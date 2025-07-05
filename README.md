# Fawry-Internship-Challenge
# 🛒 C++ E-Commerce Cart System

This project is a console-based C++ application that simulates a basic e-commerce cart system. It demonstrates the use of **Object-Oriented Programming (OOP)** principles such as **abstraction**, **inheritance**, **polymorphism**, and **encapsulation**.

## 🚀 Features

- Add shippable and non-shippable products to a customer's cart
- Enforce rules (e.g., expired or out-of-stock items cannot be added)
- Calculate:
  - Total item cost
  - Total shipping fees
  - Final amount after checkout
- Track customer's balance and deduct purchases
- Generate a formatted checkout receipt
- Calculate total shipping weight
- Use runtime polymorphism via abstract classes and virtual methods

## 🧱 Object-Oriented Design

| Class               | Responsibility                                                   |
|--------------------|------------------------------------------------------------------|
| `Customer`         | Stores user info and manages balance                             |
| `Product` (abstract)| Base class with pure virtual methods for all products            |
| `Shippable_Product`| Inherits from `Product`; calculates weight and shipping fees     |
| `NonShippable_Product` | Inherits from `Product`; excludes shipping calculations    |
| `Cart`             | Handles product addition, validation, cost calculations          |
| `shipping_service` | Outputs shipping label with total package weight                 |