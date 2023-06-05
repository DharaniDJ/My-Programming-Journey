# Programming Challenge Description

# You a writing a program to analyze the financial data for a set of companies.
# Your coworker gives you a text of company data. However, you are worried that
# your coworker didn't typr the data in correctly. Write a program that will tell
# you if the data is correctly formatted

# INPUT 1

# [
#     {
#         company_name: (BlackRock)
#         ticker: (BLK)
#         stock_price: {
#             2022-04-03: ($930)
#             2022-04-02: ($932)
#         }
#     },
#     {
#         company_name: (Apple)
#         ticker: (APPL)
#         stock_price: {
#             2022-04-03: ($175)
#             2022-04-02: ($178)
#         }
#     }
# ]

# OUTPUT
# valid

#################################################################

# INPUT 2

# [
#     {
#         company_name: (BlackRock(
#         ticker: (BLK{
#         stock_price: {
#             2022-04-03: ($930]
#             2022-04-02: ($932}
#         }
#     }
# ]

# OUTPUT
# invalid

#################################################################


def solve():
    stack = []
    open_list = ['[','{','(']
    close_list = ["]","}",')']
    for line in sys.stdin:
        if i in line:
            if i in open_list:
                stack.append(i)
            elif i in close_list:
                pos = close_list.index(i)
                if((len(stack) > 0) and (open_list[pos]==stack[len(stack)-1])):
                    stack.pop()
                else:
                    print("invalid")
                    return
        
        if len(stack) == 0:
            print("valid")
        else:
            print("invalid")

solve()