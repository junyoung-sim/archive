#!/usr/bin/env python3

from modules import *
from prettytable import PrettyTable

if __name__ == "__main__":
    portfolio_count = 1
    print("List of portfolios:\n")
    for p in listPortfolios():
        print("#{}: {}" .format(portfolio_count, p))
        portfolio_count += 1
    print("\n----------------------------------------------------\n")

    portfolio = input("Type in portfolio name listed above: ")
    ids, names, goal, shares, cash = load(portfolio)

    total_asset, stock_asset, prices = cash, [], []
    for i in range(len(ids)):
        stock, dates = YahooFinance(ids[i], "2019-01-01")
        if ids[i] == "300750.SZ":
            stock[-1] = 30.81
        prices.append(stock[-1])
        stock_asset.append(prices[-1] * shares[i])
        total_asset += stock_asset[-1]
    
    percentage = [asset * 100 / total_asset for asset in stock_asset]
    percentage_diff = [(percentage[i] - goal[i]) * 100 / goal[i] for i in range(len(names))]
    profit = [stock_asset[i] - (goal[i] * total_asset / 100) for i in range(len(names))]
    trades = [profit[i] / prices[i] for i in range(len(names))]

    table = PrettyTable()
    table.field_names = ['Name', 'Shares', 'Goal', 'Percentage Diff', 'Trades']
    for i in range(len(names)):
        table.add_row([names[i], shares[i], goal[i], percentage_diff[i], trades[i]])
    print("\n", table)
    print("Cash: ", cash)
    print("Evaluated total asset: {}\n" .format(total_asset)) 
