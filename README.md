# CSV Excel Parser

Application that parses primitive excel-like formulas. This app is able to evaluate formulas recursively, so cell formulas
can refer to cells with formulas. Evaluator also checks for loops in formulas.

Supports following operations (ARG can be a number or cell address):
- ARG1 + ARG2
- ARG1 - ARG2
- ARG1 * ARG2
- ARG1 / ARG2
