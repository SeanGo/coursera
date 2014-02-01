getmonitor <- function(id, directory, summarize = FALSE) {
        ## 'id' is a vector of length 1 indicating the monitor ID
        ## number. The user can specify 'id' as either an integer, a
        ## character, or a numeric.
        
        ## 'directory' is a character vector of length 1 indicating
        ## the location of the CSV files

        ## 'summarize' is a logical indicating whether a summary of
        ## the data should be printed to the console; the default is
        ## FALSE
        
        ## Your code here

	#first chance to catch id error or directory param error
	#n is total number of pm data, get from list.files() function
	#id must be in 1:n
	n <- length(list.files(paste('./', directory, sep='')))
	if (n < 1) {
		print(paste('The directory', directory, ' is empty or do not exist'))
		stop();
	}
	nid <- as.integer(id)	
	if (nid < 1 | nid > n) {
		print(paste('The id must be in 1 :', n));
		stop();
	}

	#try to read data and capture error
	tryCatch ({
		#read data from file
		filepath <- sprintf('./%s/%03d.csv', directory, nid);
	        data <- data.frame(read.csv(filepath))
		#get the summary of data if summarize was set to true
		if (TRUE == summarize)
			print(summary(data))
	}, error = function(err) {
		#print error message
		print(err)
		#print my error message
		print(paste('The id', id, 'data might do not exist or the data file is bad'))
		#return a error message line
		data <- paste('Can not read data with id', id)
	}) # END tryCatch

	return (data)
}

#head(getmonitor(123, 'specdata'))
#head(getmonitor(123, 'specdata', TRUE))
#head(getmonitor(1, 'specdata'))
#head(getmonitor(0, 'specdata'))
#head(getmonitor(0, '0'))

