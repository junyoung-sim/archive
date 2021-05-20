
import math

def normalize(matrix):
    normalized = [(val - min(matrix)) / (max(matrix) - min(matrix)) for val in matrix]
    return normalized

def TimeframeProfit(data):
    return (data[-1] - data[0]) / data[0]

def AnnualProfit(data):
    annual_profit = 0.00
    try:
        profit = [TimeframeProfit(data[i:i+180]) for i in range(0, len(data)-360, 180)]
        annual_profit = sum(profit) / len(profit)
    except Exception as e: # when data is too short
        annual_profit = TimeframeProfit(data)
    #annual_profit = 1.00 if annual_profit > 0.00 else 0.00
    return annual_profit

def MovingAvg(data, window=50, stride=1):
    trend = [sum(data[i:i+window]) / window for i in range(0, len(data) - window, stride)]
    data = data[:len(trend)]
    # calculate the percentage of the stock line remaining above the trend line
    growth_frequency = sum([1 for i in range(len(data)) if data[i] > trend[i]]) / len(data)
    return growth_frequency

def Sensitivity(data):
    change = [(data[i + 1] - data[i]) * 100 / data[i] for i in range(0, len(data) - 1)]
    average = sum(change) / len(change)
    standard_deviation = math.sqrt(sum([(val - average)**2 for val in change]) / len(change))
    # calculate the percentage of deviation values within the standard dev.
    within_standard = [1 for val in change if abs(val - average) < standard_deviation]
    sensitivity = sum(within_standard) / len(change)
    return sensitivity

def Acceleration(data, delta_range):
    change = [(data[i + delta_range] - data[i]) / delta_range for i in range(0, len(data) - delta_range, delta_range)]
    acceleration = [(change[i + delta_range] - change[i]) / delta_range for i in range(0, len(change) - delta_range, delta_range)]
    # calculate the increase : decrease ratio based on the stock's acceleration
    increase = sum([1 for val in acceleration if val > 0.00])
    decrease = len(acceleration) - increase
    acceleration_based_growth_ratio = increase / decrease
    return acceleration_based_growth_ratio

def MatchData(stock, stock_dates, gold, gold_dates):
    adjusted_gold_dates, adjusted_gold_data = [], []
    for i in range(len(gold)):
        if gold_dates[i] in stock_dates:
            adjusted_gold_dates.append(gold_dates[i])
            adjusted_gold_data.append(gold[i])
    adjusted_stock_dates, adjusted_stock_data, adjusted_stock_vol = [], [], []
    for i in range(len(stock)):
        if stock_dates[i] in adjusted_gold_dates:
            adjusted_stock_dates.append(stock_dates[i])
            adjusted_stock_data.append(stock[i])
    return adjusted_stock_data, adjusted_gold_data
