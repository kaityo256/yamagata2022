balance = 100000
y_rate = 0.15  # Yearly rate
m_rate = y_rate / 12.0  # Monthly rate
payment = 5000  # Monthly payment

i = 0
while balance > 0:
    i = i + 1
    interest = int(balance * m_rate)
    pay = payment - interest
    if balance < pay:
        pay = balance
    balance -= pay
    print(f"{i} {interest} {pay} {interest + pay} {balance}")
