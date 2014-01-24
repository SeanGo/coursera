
##########################################################################
#Part1
outcome <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
head(outcome)
outcome[, 11] <- as.numeric(outcome[, 11])
hist(outcome[, 11], xlab="Shit Days", ylab = "Fuck Times", main="Ha Ha ha")

###########################################################################
# Part2

#get the deat reate data of HA, HF, Pneu
death_reate_30 <- outcome[, c(11, 17, 23)]
death_reate_30[,1]<-as.numeric(death_reate_30[,1])
death_reate_30[,2]<-as.numeric(death_reate_30[,2])
death_reate_30[,3]<-as.numeric(death_reate_30[,3])

## prepare the lable and titles
xLab <- "30−day Death Rate"; yLab <- "Frequency"
title <- vector(mode="character")
title[1] <- "Heart Attack"; title[2] <- "Heart Failure"; title[3] <- "Pneumonia"
#set cols vector for death_reate_30 dataframe
cols <- (1:3)
#get the range of days
xrange = range(death_reate_30, na.rm = TRUE)


#--------- Draw the first Graph --------------------
#split the graph to 3 rows and 1 col
par(mfrow = c(3, 1))
draw_hist_1 <- function(x) {
	hist(death_reate_30[,x],
		xlab=xLab,
		ylab=yLab,
		main=title[x],
		xlim=xrange)
}

#hist return a list as result, so sapply retuan a matrix to store the result
draw_result <- sapply(cols, draw_hist_1)

#--------- Draw the second Graph --------------------
#split the graph to 1 row and 3 cols
draw_hist_2 <- function(x) {
	med <- median(death_reate_30[,x], na.rm = TRUE)
	result <- hist(death_reate_30[,x],
			xlab=xLab, 
			ylab=yLab,
			main=substitute(T * (bar(X) == k), list(T = title[x], k = med)),
			xlim=xrange,
			prob=TRUE)
	abline(v = med)
	lines(density(death_reate_30[,x], na.rm=TRUE), col=2)
}

par(mfrow = c(1, 3))
draw_result <- sapply(cols, draw_hist_2)

#########################################################################
# Part 3

#Subset the original dataset and exclude states that contain less than 20 hospitals.
StateTable <-as.data.frame(table(outcome$State))
outcome2<-outcome[outcome$State %in% StateTable[StateTable$Freq >20,]$Var1,]

death <- as.numeric(outcome2[, 11])
tate <- outcome2$State
boxplot(death ~ state,
        ylab = "30-day Death Rate",
	main="30-day Death Rate",
	par(las=2))


###################################################
## Part 4
library(lattice)

outcome <- read.csv("outcome-of-care-measures.csv", colClasses = "character")
hospital <- read.csv("hospital-data.csv", colClasses = "character")
death <- as.numeric(outcome.hospital[, 11]) ## Heart attack outcome
npatient <- as.numeric(outcome.hospital[, 15])
owner <- factor(outcome.hospital$Hospital.Ownership)
xyplot(death ~ npatient | owner,
	data = outcome.hospital,
	main = "Heart Attack 30−day Death Rate by Ownership",
	xlab = "Number of Patients Seen",
	ylab = "Heart Attack 30-day Death Rate",
	font = 7,
	panel = function(x, y, ...) {
		panel.xyplot(x, y, ...)
		fit <- lm(y ~ x)
		panel.abline(fit)
	}
	)


