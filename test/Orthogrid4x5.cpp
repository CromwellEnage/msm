// Copyright 2018 Cromwell D. Enage
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

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
}

#include <boost/msm/front/state_machine_def.hpp>
#include <boost/fusion/container/map.hpp>
#include <boost/fusion/sequence/intrinsic/at_key.hpp>
#include <boost/fusion/support/pair.hpp>
#include <boost/mpl/integral_c.hpp>

namespace test {

    template <unsigned int Row, unsigned int Column>
    class state_room : public boost::msm::front::state<>
    {
        boost::fusion::map<
            boost::fusion::pair<test::event_up,unsigned int>
          , boost::fusion::pair<test::event_down,unsigned int>
          , boost::fusion::pair<test::event_left,unsigned int>
          , boost::fusion::pair<test::event_right,unsigned int>
        > entry_count;
        boost::fusion::map<
            boost::fusion::pair<test::event_up,unsigned int>
          , boost::fusion::pair<test::event_down,unsigned int>
          , boost::fusion::pair<test::event_left,unsigned int>
          , boost::fusion::pair<test::event_right,unsigned int>
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
            return boost::fusion::at_key<Event>(entry_count);
        }

        template <typename Event>
        unsigned int get_exit_count() const
        {
            return boost::fusion::at_key<Event>(exit_count);
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

    typedef test::state_room<0,0> state_room_0_0;
    typedef test::state_room<0,1> state_room_0_1;
    typedef test::state_room<0,2> state_room_0_2;
    typedef test::state_room<0,3> state_room_0_3;
    typedef test::state_room<0,4> state_room_0_4;
    typedef test::state_room<1,0> state_room_1_0;
    typedef test::state_room<1,1> state_room_1_1;
    typedef test::state_room<1,2> state_room_1_2;
    typedef test::state_room<1,3> state_room_1_3;
    typedef test::state_room<1,4> state_room_1_4;
    typedef test::state_room<2,0> state_room_2_0;
    typedef test::state_room<2,1> state_room_2_1;
    typedef test::state_room<2,2> state_room_2_2;
    typedef test::state_room<2,3> state_room_2_3;
    typedef test::state_room<2,4> state_room_2_4;
    typedef test::state_room<3,0> state_room_3_0;
    typedef test::state_room<3,1> state_room_3_1;
    typedef test::state_room<3,2> state_room_3_2;
    typedef test::state_room<3,3> state_room_3_3;
    typedef test::state_room<3,4> state_room_3_4;
}

#include <boost/msm/back/state_machine.hpp>
#include <boost/fusion/container/deque.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/core/lightweight_test.hpp>

namespace test {

    // front-end: define the FSM structure 
    struct walker_
      : public boost::msm::front::state_machine_def<test::walker_>
    {
        typedef test::state_room_0_0 initial_state;

        walker_()
          : boost::msm::front::state_machine_def<test::walker_>()
        {
        }

        struct transition_table
          : boost::fusion::deque<
                _row<
                    test::state_room_0_0
                  , test::event_up
                  , test::state_room_3_0
                >
              , _row<
                    test::state_room_0_0
                  , test::event_down
                  , test::state_room_1_0
                >
              , _row<
                    test::state_room_0_0
                  , test::event_left
                  , test::state_room_0_4
                >
              , _row<
                    test::state_room_0_0
                  , test::event_right
                  , test::state_room_0_1
                >
              , _row<
                    test::state_room_0_1
                  , test::event_up
                  , test::state_room_3_1
                >
              , _row<
                    test::state_room_0_1
                  , test::event_down
                  , test::state_room_1_1
                >
              , _row<
                    test::state_room_0_1
                  , test::event_left
                  , test::state_room_0_0
                >
              , _row<
                    test::state_room_0_1
                  , test::event_right
                  , test::state_room_0_2
                >
              , _row<
                    test::state_room_0_2
                  , test::event_up
                  , test::state_room_3_2
                >
              , _row<
                    test::state_room_0_2
                  , test::event_down
                  , test::state_room_1_2
                >
              , _row<
                    test::state_room_0_2
                  , test::event_left
                  , test::state_room_0_1
                >
              , _row<
                    test::state_room_0_2
                  , test::event_right
                  , test::state_room_0_3
                >
              , _row<
                    test::state_room_0_3
                  , test::event_up
                  , test::state_room_3_3
                >
              , _row<
                    test::state_room_0_3
                  , test::event_down
                  , test::state_room_1_3
                >
              , _row<
                    test::state_room_0_3
                  , test::event_left
                  , test::state_room_0_2
                >
              , _row<
                    test::state_room_0_3
                  , test::event_right
                  , test::state_room_0_4
                >
              , _row<
                    test::state_room_0_4
                  , test::event_up
                  , test::state_room_3_4
                >
              , _row<
                    test::state_room_0_4
                  , test::event_down
                  , test::state_room_1_4
                >
              , _row<
                    test::state_room_0_4
                  , test::event_left
                  , test::state_room_0_3
                >
              , _row<
                    test::state_room_0_4
                  , test::event_right
                  , test::state_room_0_0
                >
              , _row<
                    test::state_room_1_0
                  , test::event_up
                  , test::state_room_0_0
                >
              , _row<
                    test::state_room_1_0
                  , test::event_down
                  , test::state_room_2_0
                >
              , _row<
                    test::state_room_1_0
                  , test::event_left
                  , test::state_room_1_4
                >
              , _row<
                    test::state_room_1_0
                  , test::event_right
                  , test::state_room_1_1
                >
              , _row<
                    test::state_room_1_1
                  , test::event_up
                  , test::state_room_0_1
                >
              , _row<
                    test::state_room_1_1
                  , test::event_down
                  , test::state_room_2_1
                >
              , _row<
                    test::state_room_1_1
                  , test::event_left
                  , test::state_room_1_0
                >
              , _row<
                    test::state_room_1_1
                  , test::event_right
                  , test::state_room_1_2
                >
              , _row<
                    test::state_room_1_2
                  , test::event_up
                  , test::state_room_0_2
                >
              , _row<
                    test::state_room_1_2
                  , test::event_down
                  , test::state_room_2_2
                >
              , _row<
                    test::state_room_1_2
                  , test::event_left
                  , test::state_room_1_1
                >
              , _row<
                    test::state_room_1_2
                  , test::event_right
                  , test::state_room_1_3
                >
              , _row<
                    test::state_room_1_3
                  , test::event_up
                  , test::state_room_0_3
                >
              , _row<
                    test::state_room_1_3
                  , test::event_down
                  , test::state_room_2_3
                >
              , _row<
                    test::state_room_1_3
                  , test::event_left
                  , test::state_room_1_2
                >
              , _row<
                    test::state_room_1_3
                  , test::event_right
                  , test::state_room_1_4
                >
              , _row<
                    test::state_room_1_4
                  , test::event_up
                  , test::state_room_0_4
                >
              , _row<
                    test::state_room_1_4
                  , test::event_down
                  , test::state_room_2_4
                >
              , _row<
                    test::state_room_1_4
                  , test::event_left
                  , test::state_room_1_3
                >
              , _row<
                    test::state_room_1_4
                  , test::event_right
                  , test::state_room_1_0
                >
              , _row<
                    test::state_room_2_0
                  , test::event_up
                  , test::state_room_1_0
                >
              , _row<
                    test::state_room_2_0
                  , test::event_down
                  , test::state_room_3_0
                >
              , _row<
                    test::state_room_2_0
                  , test::event_left
                  , test::state_room_2_4
                >
              , _row<
                    test::state_room_2_0
                  , test::event_right
                  , test::state_room_2_1
                >
              , _row<
                    test::state_room_2_1
                  , test::event_up
                  , test::state_room_1_1
                >
              , _row<
                    test::state_room_2_1
                  , test::event_down
                  , test::state_room_3_1
                >
              , _row<
                    test::state_room_2_1
                  , test::event_left
                  , test::state_room_2_0
                >
              , _row<
                    test::state_room_2_1
                  , test::event_right
                  , test::state_room_2_2
                >
              , _row<
                    test::state_room_2_2
                  , test::event_up
                  , test::state_room_1_2
                >
              , _row<
                    test::state_room_2_2
                  , test::event_down
                  , test::state_room_3_2
                >
              , _row<
                    test::state_room_2_2
                  , test::event_left
                  , test::state_room_2_1
                >
              , _row<
                    test::state_room_2_2
                  , test::event_right
                  , test::state_room_2_3
                >
              , _row<
                    test::state_room_2_3
                  , test::event_up
                  , test::state_room_1_3
                >
              , _row<
                    test::state_room_2_3
                  , test::event_down
                  , test::state_room_3_3
                >
              , _row<
                    test::state_room_2_3
                  , test::event_left
                  , test::state_room_2_2
                >
              , _row<
                    test::state_room_2_3
                  , test::event_right
                  , test::state_room_2_4
                >
              , _row<
                    test::state_room_2_4
                  , test::event_up
                  , test::state_room_1_4
                >
              , _row<
                    test::state_room_2_4
                  , test::event_down
                  , test::state_room_3_4
                >
              , _row<
                    test::state_room_2_4
                  , test::event_left
                  , test::state_room_2_3
                >
              , _row<
                    test::state_room_2_4
                  , test::event_right
                  , test::state_room_2_0
                >
              , _row<
                    test::state_room_3_0
                  , test::event_up
                  , test::state_room_2_0
                >
              , _row<
                    test::state_room_3_0
                  , test::event_down
                  , test::state_room_0_0
                >
              , _row<
                    test::state_room_3_0
                  , test::event_left
                  , test::state_room_3_4
                >
              , _row<
                    test::state_room_3_0
                  , test::event_right
                  , test::state_room_3_1
                >
              , _row<
                    test::state_room_3_1
                  , test::event_up
                  , test::state_room_2_1
                >
              , _row<
                    test::state_room_3_1
                  , test::event_down
                  , test::state_room_0_1
                >
              , _row<
                    test::state_room_3_1
                  , test::event_left
                  , test::state_room_3_0
                >
              , _row<
                    test::state_room_3_1
                  , test::event_right
                  , test::state_room_3_2
                >
              , _row<
                    test::state_room_3_2
                  , test::event_up
                  , test::state_room_2_2
                >
              , _row<
                    test::state_room_3_2
                  , test::event_down
                  , test::state_room_0_2
                >
              , _row<
                    test::state_room_3_2
                  , test::event_left
                  , test::state_room_3_1
                >
              , _row<
                    test::state_room_3_2
                  , test::event_right
                  , test::state_room_3_3
                >
              , _row<
                    test::state_room_3_3
                  , test::event_up
                  , test::state_room_2_3
                >
              , _row<
                    test::state_room_3_3
                  , test::event_down
                  , test::state_room_0_3
                >
              , _row<
                    test::state_room_3_3
                  , test::event_left
                  , test::state_room_3_2
                >
              , _row<
                    test::state_room_3_3
                  , test::event_right
                  , test::state_room_3_4
                >
              , _row<
                    test::state_room_3_4
                  , test::event_up
                  , test::state_room_2_4
                >
              , _row<
                    test::state_room_3_4
                  , test::event_down
                  , test::state_room_0_4
                >
              , _row<
                    test::state_room_3_4
                  , test::event_left
                  , test::state_room_3_3
                >
              , _row<
                    test::state_room_3_4
                  , test::event_right
                  , test::state_room_3_0
                >
            >
        {
        };

        // Replaces the default no-transition response.
        template <typename FSM, typename Event>
        void no_transition(Event const&, FSM&, int)
        {
            BOOST_TEST(false);
        }

        // no-op
        template <typename Event, typename FSM>
        void on_entry(Event const&, FSM& fsm) 
        {
        }
    };

    // Pick a back-end
    typedef boost::msm::back::state_machine<test::walker_> walker;
}

int main()
{
    test::walker w;
    BOOST_TEST_EQ(0, w.current_state()[0]);

    w.process_event(test::event_down());
    BOOST_TEST_EQ(5, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_0&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_0&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(10, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_0&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_0&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(15, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_0&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_0&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_right());
    BOOST_TEST_EQ(16, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_0&>().get_exit_count<
            test::event_right
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_1&>().get_entry_count<
            test::event_right
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(11, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_1&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_1&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(6, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_1&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_1&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(1, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_1&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_1&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_right());
    BOOST_TEST_EQ(2, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_1&>().get_exit_count<
            test::event_right
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_2&>().get_entry_count<
            test::event_right
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(7, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_2&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_2&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(12, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_2&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_2&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(17, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_2&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_2&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_right());
    BOOST_TEST_EQ(18, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_2&>().get_exit_count<
            test::event_right
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_3&>().get_entry_count<
            test::event_right
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(13, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_3&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_3&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(8, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_3&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_3&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(3, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_3&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_3&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_right());
    BOOST_TEST_EQ(4, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_3&>().get_exit_count<
            test::event_right
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_4&>().get_entry_count<
            test::event_right
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(9, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_4&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_4&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(14, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_4&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_4&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(19, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_4&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_4&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_right());
    BOOST_TEST_EQ(15, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_4&>().get_exit_count<
            test::event_right
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_0&>().get_entry_count<
            test::event_right
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(10, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_0&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_0&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(5, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_0&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_0&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(0, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_0&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_0&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_left());
    BOOST_TEST_EQ(4, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_0&>().get_exit_count<
            test::event_left
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_4&>().get_entry_count<
            test::event_left
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(19, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_4&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_4&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(14, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_4&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_4&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(9, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_4&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_4&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_left());
    BOOST_TEST_EQ(8, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_4&>().get_exit_count<
            test::event_left
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_3&>().get_entry_count<
            test::event_left
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(13, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_3&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_3&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(18, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_3&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_3&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(3, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_3&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_3&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_left());
    BOOST_TEST_EQ(2, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_3&>().get_exit_count<
            test::event_left
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_2&>().get_entry_count<
            test::event_left
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(17, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_2&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_2&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(12, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_2&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_2&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_up());
    BOOST_TEST_EQ(7, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_2&>().get_exit_count<
            test::event_up
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_2&>().get_entry_count<
            test::event_up
        >()
    );

    w.process_event(test::event_left());
    BOOST_TEST_EQ(6, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_2&>().get_exit_count<
            test::event_left
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_1&>().get_entry_count<
            test::event_left
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(11, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_1_1&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_1&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(16, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_2_1&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_1&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_down());
    BOOST_TEST_EQ(1, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_3_1&>().get_exit_count<
            test::event_down
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_1&>().get_entry_count<
            test::event_down
        >()
    );

    w.process_event(test::event_left());
    BOOST_TEST_EQ(0, w.current_state()[0]);
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_1&>().get_exit_count<
            test::event_left
        >()
    );
    BOOST_TEST_EQ(
        1, w.get_state<test::state_room_0_0&>().get_entry_count<
            test::event_left
        >()
    );

    return boost::report_errors();
}

