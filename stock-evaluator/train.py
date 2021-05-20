#!/usr/bin/env python3

from core.core import *

if __name__ == "__main__":
    ids = GetIndexList("./index/trainlist")
    model = DeepFinance("standard-v1.2")
    model.train(ids, "2005-01-01", 500, True, True)
    cleanup()
