#!/bin/bash
g++ PortfolioTester.cpp Stock.cpp Portfolio.cpp Calendar.cpp Headline.cpp Purchase.cpp testPortfolioApp.cpp PathUtil.cpp -o tester && ./tester
