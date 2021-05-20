#!/usr/bin/env python3

from core.core import  *

if __name__ == "__main__":
    ids = GetIndexList("./index/alllist")
    model = DeepFinance("standard-v1.2")
    model.run(ids)
    cleanup()