count <- function(cause = NULL) {
	## Check that "cause" is non-NULL; else throw error
	if (is.null(cause))
		stop("The cause is an NULL")

	## read the data from file
	homicides <- readLines("homicides.txt")

	## Read "homicides.txt" data file
	## Extract causes of death
	r <- regexpr("[C|c]ause: (.*?)</dd>", homicides)
	m <- tolower(regmatches(homicides, r))
	Cause <- sapply(m, function(x) substr(x, nchar("cause: ") + 1, nchar(x) - 5))

	dfCause <- as.data.frame(table(Cause))
        
	## Check that specific "cause" is allowed; else throw error
	if (!cause %in% dfCause$Cause) {
		print("Cause must in ")
		print(levels(dfCause$Cause))
		stop()
	}
	## Return integer containing count of homicides for that cause
	return (dfCause[dfCause$Cause == cause,]$Freq)
}
