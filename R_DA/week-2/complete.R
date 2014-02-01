complete <- function(directory, id = 1:332) {
        ## 'directory' is a character vector of length 1 indicating
        ## the location of the CSV files

        ## 'id' is an integer vector indicating the monitor ID numbers
        ## to be used
        
        ## Return a data frame of the form:
        ## id nobs
        ## 1  117
        ## 2  1041
        ## ...
        ## where 'id' is the monitor ID number and 'nobs' is the
        ## number of complete cases
	tid <- as.vector(as.integer(id))
	#print(class(tid))
	#print(is.vector(tid))
	if (tid < 1 || tid > 332) {
		print("id must in 1:332")
		stop()
	}

	result <- data.frame(id = integer(0), nobs = integer(0))
	get_complate_number <- function(myid) {
		#print(myid)
		tryCatch({
			filepath <- sprintf("./%s/%03d.csv", directory, myid)
			#print(filepath)
			dataset <- data.frame(read.csv(filepath));
			#print(dim(dataset))
			n <- nrow(dataset[!is.na(dataset$Date) & !is.na(dataset$sulfate) & !is.na(dataset$nitrate) & !is.na(dataset$ID), ])
			#print(n)
			result[nrow(result) + 1,] <<- c(myid, n)
		}, error = function(err) {
			print(err)
			stop()
		})
	}

	sapply(tid, get_complate_number)
	return (result)
}

