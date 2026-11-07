# Black-Scholes Fair Value Options Chain Calculator

A C++ implementation of the Black-Scholes option pricing model. Generates a theoretical options chain displaying Call and Put premiums alongside the five standard option Greeks.

## Model Assumptions

- European-style options
- Zero dividend yield
- Constant implied volatility
- Continuously compounded risk-free rate
- No transaction costs

## 1. Time and Discounting

**Annualized Time to Expiration**

$$
T = \frac{\text{Days to Expiry}}{365}
$$

**Discount Factor**

$$
DF = e^{-rT}
$$

## 2. Gaussian Probability Functions

The model calculates two intermediate variables used to determine option premiums and sensitivities.

$$
d_1 = \frac{\ln(S/K)+(r+\frac{\sigma^2}{2})T}{\sigma\sqrt{T}}
$$

$$
d_2 = d_1-\sigma\sqrt{T}
$$

Where:

- $S$ = Underlying asset price
- $K$ = Strike price
- $r$ = Annualized risk-free rate
- $\sigma$ = Annualized implied volatility
- $T$ = Time to expiration in years
- $N(x)$ = Standard normal cumulative distribution function
- $\phi(x)$ = Standard normal probability density function

## 3. Option Premiums

**Call Option**

$$
C = SN(d_1)-KDFN(d_2)
$$

**Put Option**

$$
P = KDFN(-d_2)-SN(-d_1)
$$

These equations calculate the theoretical fair value of European-style Call and Put options.

## 4. Option Greeks

The calculator computes five standard Greeks to measure option price sensitivity.

### Delta ($\Delta$)

Measures option price sensitivity to changes in the underlying asset price.

**Call**

$$
\Delta_C=N(d_1)
$$

**Put**

$$
\Delta_P=N(d_1)-1
$$

### Gamma ($\Gamma$)

Measures the rate of change in Delta relative to the underlying asset price.

$$
\Gamma=\frac{\phi(d_1)}{S\sigma\sqrt{T}}
$$

### Theta ($\Theta$)

Measures the daily time decay of an option's theoretical value.

**Call**

$$
\Theta_C=
\frac{
-\frac{S\phi(d_1)\sigma}{2\sqrt{T}}
-rKDFN(d_2)
}{365}
$$

**Put**

$$
\Theta_P=
\frac{
-\frac{S\phi(d_1)\sigma}{2\sqrt{T}}
+rKDFN(-d_2)
}{365}
$$

### Vega

Measures option price sensitivity to changes in implied volatility.

Expressed per one percentage point of volatility:

$$
Vega=\frac{S\phi(d_1)\sqrt{T}}{100}
$$

### Rho ($\rho$)

Measures option price sensitivity to changes in the risk-free interest rate.

Expressed per one percentage point change in interest rates.

**Call**

$$
\rho_C=\frac{KTDFN(d_2)}{100}
$$

**Put**

$$
\rho_P=-\frac{KTDFN(-d_2)}{100}
$$

## 5. Options Chain Generation

The program uses a C++ `struct` to store option premiums and Greeks, alongside a `std::vector` to construct an options chain across user-defined strike intervals.

### Terminal Inputs

- Underlying asset price
- Days to expiration
- Overnight SOFR (basis points)
- Implied volatility (percentage)
- Strike interval
- Number of options to generate

### Terminal Output

- Put premiums and Greeks
- Strike prices
- Call premiums and Greeks

Premiums and Greeks are scaled by 100 for standard contract-level presentation.

## Technologies

- **C++** — Core implementation
- **STL** — Data structures and options chain generation
- **`<cmath>`** — Logarithms, exponentials, square roots and Gaussian probability calculations
- **`<vector>`** — Options chain storage
- **`<iomanip>`** — Terminal output formatting

## Purpose

An introductory quantitative finance programming project exploring Black-Scholes theoretical option pricing, interest-rate discounting, options chain construction, and option risk sensitivities.
