Q2/ Pas de probleme de data race, les threads ne peuvent pas debiter ou crediter un compte en meme temps.

Q5/ lock avant la comparaison puis lock dans debiter donc blocage car on ne fait pas attention à la propriété du mutex.

q6/ Du fait de l'ordre des debits et credits, en effet, un thread peut avoir un debiteur qui sera crediteur pour un autre thread et inversement. Donc toujours un probleme d'interblocage.

q7/ Non, car un comptable pourrait se positionner entre une operation de débit et crédit. Ce qui provoquerait une erreur de solde.

q9/
q10/


