# Copyright 2018 Cromwell D. Enage
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5)
project(BoostMSM)

add_library(boost_msm INTERFACE)
add_library(Boost::msm ALIAS boost_msm)

target_include_directories(boost_msm INTERFACE include)

target_link_libraries(boost_msm
    INTERFACE
        Boost::config
        Boost::static_assert
)

