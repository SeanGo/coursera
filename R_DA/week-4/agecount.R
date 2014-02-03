agecount <- function(age = NULL) {
	## Check that "cause" is non-NULL; else throw error
	if (is.null(age))
		stop("the age muse be an integer")

	## read the data from file
	homicides <- readLines("homicides.txt")
	
	## Extract ages of victims; ignore records where no age is
## given
	r <- regexpr("[0-9]* years old", homicides, ignore.case = TRUE)
	m <- regmatches(homicides, r)
	Age <- sapply(m, function(x) substr(x, 1, nchar(x) - nchar(" years old")))
	dfAge <- as.data.frame(table(Age))
       
	## Return integer containing count of homicides for that age
	if (!age %in% dfAge$Age)
		return (0);
	else
		return (dfAge[dfAge$Age == age,]$Freq)
}
