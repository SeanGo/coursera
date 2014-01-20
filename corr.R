corr <- function(directory, threshold = 0) {
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
	tid <- 1 : length(list.files(paste('./', directory, sep='')))

	result   <- as.numeric(vector())
	get_data <- function(myid) {
		#print(myid)
		tryCatch({
			filepath <- sprintf("./%s/%03d.csv", directory, myid)
			#print(filepath)
			dataset <- data.frame(read.csv(filepath));
			#print(dim(dataset))
			sub <- dataset[!is.na(dataset$Date) & !is.na(dataset$sulfate) & !is.na(dataset$nitrate) & !is.na(dataset$ID), ]
			if (nrow(sub) > threshold) {
				result[length(result) + 1] <<- cor(sub$sulfate, sub$nitrate)
			}
		}, error = function(err) {
			print(err)
			stop()
		})
	}

	sapply(tid, get_data)
	return (result)
}

