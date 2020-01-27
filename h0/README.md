You are working on a larger project. The leader already has some specs for what is needed and is 
giving to you only what you need to do, other people work on other parts. YOU need to provide all 
that is asked exactly as asked, and nothing else.


You are asked to implement functions f1(), f2(), f3() and provide one global variable g, all 
available to others on the project. You are also asked to provide macros M, also available 
to others.


In implementing f2() and f3() you decided they two must access a helper global variable g23 
(it should not be exposed to others). In implementing f1() you noticed it was getting long 
so you separated some of the code into a separate helper function f1a() called from f1(). 
The helper also needs a special macro M1a.


Main is not your responsibility.


Propose architecture for what you are doing. Skip all unnecessary details such as types, 
interfaces, bodies and calls but show with exact names: all sources, with all headers 
or variables/macros. For headers, add inclusion prevention.


To make grading simpler, submit one file, computer or hand generated, following the 
example in your notes. If typed, clearly identify the beginning, end and name of each file. 
If drawn, you may use boxes to identify the beginning and end.


Note: the answer should be about C. Do not mix OO concepts or concepts specific to other 
languages which affect linking and thus architecture.

