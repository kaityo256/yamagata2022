

def num_payment(balance, y_rate, payment):
    y_rate = 0.15  # Yearly rate
    i = 0
    while balance > 0:
        i = i + 1
        interest = int(balance * m_rate)
        pay = payment - interest
        if balance < pay:
            pay = balance
        balance -= pay
        print(f"{i} {interest} {pay} {interest + pay} {balance}")

balance = 100000
y_rate = 0.15  # Yearly rate
payment = 5000  # Monthly payment
num_payment(balance, y_rate, payment)
