rankall <- function(outcome, num = "best") {
	## Read outcome data
	## Check that state and outcome are valid
	## Return hospital name in that state with the given rank
	## 30-day death rate

	colno <- c(11, 17, 23)
	reason<- c("heart attack", "heart failure", "pneumonia")
	dfReason <- as.data.frame(cbind(colno, reason))
	dfReason$colno <- as.numeric(as.character(dfReason$colno))
        selected_col <- dfReason[dfReason$reason == outcome, "colno"]

	if (!outcome %in% dfReason$reason)
		stop("invalid outcome")

	dfOutcome <- as.data.frame(read.csv("outcome-of-care-measures.csv", colClasses = "character"))
	dfOutcome[,11]<- as.numeric(dfOutcome[,11])
        dfOutcome[,17]<- as.numeric(dfOutcome[,17])
        dfOutcome[,23]<- as.numeric(dfOutcome[,23])

	dfState  <- as.data.frame(table(dfOutcome$State))
	vecState <- as.vector(dfState[order(dfState$Var1), 1])

	get_hospital <- function(theState) {
		df  <- na.omit(subset(dfOutcome, dfOutcome$State == theState, select = c(selected_col, Hospital.Name) ))

	        thenum <- 0
        	if (as.character(num) == "best")
                	thenum <- 1
	        else if (as.character(num) == "worst")
        	        thenum <- nrow(df)

	        if (thenum == 0) {
        	        if (as.numeric(num) > nrow(df)
                	        | as.numeric(num) < 1)
                        	return (NA)
	                thenum <- as.numeric(num)
        	}

		return (df[order(df[,1], df[,2], na.last=NA),][thenum, "Hospital.Name"])
	}
 
	hname <- sapply(vecState, get_hospital)
	dfRank <- data.frame(cbind(hname, vecState), row.names = vecState)
	colnames(dfRank) <- c("hospital", "state")
	return (dfRank)
}

#source("best.R")
#best("TX", "heart attack")
#best("TX", "heart failure")
#best("MD", "heart attack")
#best("MD", "pneumonia")

#best("BB", "heart attack")
#best("NY", "hert attack")

