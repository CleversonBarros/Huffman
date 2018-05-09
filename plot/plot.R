

battle <- read.csv("base.csv", header=TRUE, sep=",", as.is=TRUE)

plot(battle)

------------------------------------------

plot(battle$LIST, type="l", xaxt = "n", col="red", ann=FALSE)

axis(1, at=1:10000, battle$N_ELEMENTS)

lines(battle$B_TREE, type="o", col="blue")

title(xlab="CASES", col.lab=rgb(0,0.5,0))
title(ylab="COMPARISONS", col.lab=rgb(0,0.5,0))
title(main="Binary Search Tree VS Linked List", col.main="black", font.main=2)
