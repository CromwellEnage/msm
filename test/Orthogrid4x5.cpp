// Copyright 2018 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/fusion/container/deque.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/mpl/integral_c.hpp>
#include <iostream>

#ifndef BOOST_MSM_NONSTANDALONE_TEST
#define BOOST_TEST_MODULE MyTest
#endif

#include <boost/test/unit_test.hpp>

namespace test {

    struct event_up
    {
    };

    struct event_down
    {
    };

    struct event_left
    {
    };

    struct event_right
    {
    };

    template <unsigned int Row, unsigned int Column>
    class state_room : public boost::msm::front::state<>
    {
        boost::fusion::map<
            boost::fusion::pair<test::event_up>
          , boost::fusion::pair<test::event_down>
          , boost::fusion::pair<test::event_left>
          , boost::fusion::pair<test::event_right>
        > entry_count;
        boost::fusion::map<
            boost::fusion::pair<test::event_up>
          , boost::fusion::pair<test::event_down>
          , boost::fusion::pair<test::event_left>
          , boost::fusion::pair<test::event_right>
        > exit_count;

     public:
        typedef boost::mpl::integral_c<unsigned int,Row> row;
        typedef boost::mpl::integral_c<unsigned int,Column> column;

        state_room()
          : boost::msm::front::state<>()
          , entry_count(
                boost::fusion::make_pair<test::event_up>(0)
              , boost::fusion::make_pair<test::event_down>(0)
              , boost::fusion::make_pair<test::event_left>(0)
              , boost::fusion::make_pair<test::event_right>(0)
            )
          , exit_count(
                boost::fusion::make_pair<test::event_up>(0)
              , boost::fusion::make_pair<test::event_down>(0)
              , boost::fusion::make_pair<test::event_left>(0)
              , boost::fusion::make_pair<test::event_right>(0)
            )
        {
        }

        template <typename Event>
        unsigned int get_entry_count() const
        {
            return boost::fusion::value_at_key<Event>(entry_count);
        }

        template <typename Event>
        unsigned int get_exit_count() const
        {
            return boost::fusion::value_at_key<Event>(exit_count);
        }

        template <typename Event, typename FSM>
        void on_entry(Event const&, FSM&)
        {
            ++boost::fusion::at_key<Event>(entry_count);
        }

        template <typename Event, typename FSM>
        void on_exit(Event const&, FSM&)
        {
            ++boost::fusion::at_key<Event>(exit_count);
        }
    };

    // front-end: define the FSM structure 
    class walker_ : public boost::msm::front::state_machine_def<test::walker_>
    {
        typedef state_room<0,0> state_room_0_0;
        typedef state_room<0,1> state_room_0_1;
        typedef state_room<0,2> state_room_0_2;
        typedef state_room<0,3> state_room_0_3;
        typedef state_room<0,4> state_room_0_4;
        typedef state_room<1,0> state_room_1_0;
        typedef state_room<1,1> state_room_1_1;
        typedef state_room<1,2> state_room_1_2;
        typedef state_room<1,3> state_room_1_3;
        typedef state_room<1,4> state_room_1_4;
        typedef state_room<2,0> state_room_2_0;
        typedef state_room<2,1> state_room_2_1;
        typedef state_room<2,2> state_room_2_2;
        typedef state_room<2,3> state_room_2_3;
        typedef state_room<2,4> state_room_2_4;
        typedef state_room<3,0> state_room_3_0;
        typedef state_room<3,1> state_room_3_1;
        typedef state_room<3,2> state_room_3_2;
        typedef state_room<3,3> state_room_3_3;
        typedef state_room<3,4> state_room_3_4;

        unsigned int current_row;
        unsigned int current_column;

     public:
        typedef state_room_0_0 initial_state;

        walker_()
          : boost::msm::front::state_machine_def<test::walker_>()
          , current_row(0)
          , current_column(0)
        {
        }

        void walk(test::up const&)
        {
            if (current_row)
            {
                --current_row;
            }
            else
            {
                current_row = 3;
            }
        }

        void walk(test::down const&)
        {
            if (current_row == 3)
            {
                current_row = 0;
            }
            else
            {
                ++current_row;
            }
        }

        void walk(test::left const&)
        {
            if (current_column)
            {
                --current_column;
            }
            else
            {
                current_column = 4;
            }
        }

        void walk(test::right const&)
        {
            if (current_column == 4)
            {
                current_column = 0;
            }
            else
            {
                ++current_column;
            }
        }

        struct transition_table
          : boost::fusion::deque<
                boost::msm::front::a_row<
                    state_room_0_0
                  , test::event_up
                  , state_room_3_0
                >
            >

        // Transition table for player
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action               Guard
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Stopped , play        , Playing , &p::start_playback                         >,
          a_row < Stopped , open_close  , Open    , &p::open_drawer                            >,
           _row < Stopped , stop        , Stopped                                              >,
            //  +---------+-------------+---------+---------------------+----------------------+
          g_row < Open    , open_close  , Empty   ,                      &p::can_close_drawer  >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Empty   , open_close  , Open    , &p::open_drawer                            >,
            row < Empty   , cd_detected , Stopped , &p::store_cd_info   ,&p::good_disk_format  >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Playing , stop        , Stopped , &p::stop_playback                          >,
          a_row < Playing , pause       , Paused  , &p::pause_playback                         >,
          a_row < Playing , open_close  , Open    , &p::stop_and_open                          >,
            //  +---------+-------------+---------+---------------------+----------------------+
          a_row < Paused  , end_pause   , Playing , &p::resume_playback                        >,
          a_row < Paused  , stop        , Stopped , &p::stop_playback                          >,
          a_row < Paused  , open_close  , Open    , &p::stop_and_open                          >
            //  +---------+-------------+---------+---------------------+----------------------+
        > {};
        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& , FSM&,int)
        {
            BOOST_FAIL("no_transition called!");
        }
        // init counters
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& fsm) 
        {
            fsm.template get_state<player_::Stopped&>().entry_counter=0;
            fsm.template get_state<player_::Stopped&>().exit_counter=0;
            fsm.template get_state<player_::Open&>().entry_counter=0;
            fsm.template get_state<player_::Open&>().exit_counter=0;
            fsm.template get_state<player_::Empty&>().entry_counter=0;
            fsm.template get_state<player_::Empty&>().exit_counter=0;
            fsm.template get_state<player_::Playing&>().entry_counter=0;
            fsm.template get_state<player_::Playing&>().exit_counter=0;
            fsm.template get_state<player_::Paused&>().entry_counter=0;
            fsm.template get_state<player_::Paused&>().exit_counter=0;
        }

    };
    // Pick a back-end
    typedef msm::back::state_machine<player_> player;

//    static char const* const state_names[] = { "Stopped", "Open", "Empty", "Playing", "Paused" };


    BOOST_AUTO_TEST_CASE( my_test )
    {     
        player p;

        p.start(); 
        BOOST_CHECK_MESSAGE(p.get_state<player_::Empty&>().entry_counter == 1,"Empty entry not called correctly");

        p.process_event(open_close()); 
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 1,"Open should be active"); //Open
        BOOST_CHECK_MESSAGE(p.get_state<player_::Empty&>().exit_counter == 1,"Empty exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Open&>().entry_counter == 1,"Open entry not called correctly");

        p.process_event(open_close()); 
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 2,"Empty should be active"); //Empty
        BOOST_CHECK_MESSAGE(p.get_state<player_::Open&>().exit_counter == 1,"Open exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Empty&>().entry_counter == 2,"Empty entry not called correctly");
        BOOST_CHECK_MESSAGE(p.can_close_drawer_counter == 1,"guard not called correctly");

        p.process_event(
            cd_detected("louie, louie",DISK_DVD));
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 2,"Empty should be active"); //Empty
        BOOST_CHECK_MESSAGE(p.get_state<player_::Open&>().exit_counter == 1,"Open exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Empty&>().entry_counter == 2,"Empty entry not called correctly");

        p.process_event(
            cd_detected("louie, louie",DISK_CD)); 
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 0,"Stopped should be active"); //Stopped
        BOOST_CHECK_MESSAGE(p.get_state<player_::Empty&>().exit_counter == 2,"Empty exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Stopped&>().entry_counter == 1,"Stopped entry not called correctly");

        p.process_event(play());
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 3,"Playing should be active"); //Playing
        BOOST_CHECK_MESSAGE(p.get_state<player_::Stopped&>().exit_counter == 1,"Stopped exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Playing&>().entry_counter == 1,"Playing entry not called correctly");
        BOOST_CHECK_MESSAGE(p.start_playback_counter == 1,"action not called correctly");

        p.process_event(pause());
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 4,"Paused should be active"); //Paused
        BOOST_CHECK_MESSAGE(p.get_state<player_::Playing&>().exit_counter == 1,"Playing exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Paused&>().entry_counter == 1,"Paused entry not called correctly");

        // go back to Playing
        p.process_event(end_pause());  
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 3,"Playing should be active"); //Playing
        BOOST_CHECK_MESSAGE(p.get_state<player_::Paused&>().exit_counter == 1,"Paused exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Playing&>().entry_counter == 2,"Playing entry not called correctly");

        p.process_event(pause()); 
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 4,"Paused should be active"); //Paused
        BOOST_CHECK_MESSAGE(p.get_state<player_::Playing&>().exit_counter == 2,"Playing exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Paused&>().entry_counter == 2,"Paused entry not called correctly");

        p.process_event(stop());  
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 0,"Stopped should be active"); //Stopped
        BOOST_CHECK_MESSAGE(p.get_state<player_::Paused&>().exit_counter == 2,"Paused exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Stopped&>().entry_counter == 2,"Stopped entry not called correctly");

        p.process_event(stop());  
        BOOST_CHECK_MESSAGE(p.current_state()[0] == 0,"Stopped should be active"); //Stopped
        BOOST_CHECK_MESSAGE(p.get_state<player_::Stopped&>().exit_counter == 2,"Stopped exit not called correctly");
        BOOST_CHECK_MESSAGE(p.get_state<player_::Stopped&>().entry_counter == 3,"Stopped entry not called correctly");
    }
}

