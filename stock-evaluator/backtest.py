#!/usr/bin/env python3

from core.core import *

if __name__ == "__main__":
    model = DeepFinance("standard-v1.2")
    model.backtest(id="^GSPC")
    cleanup()
