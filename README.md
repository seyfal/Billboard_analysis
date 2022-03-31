# Billboard_analysis
C++ program that will quantify and summarize Billboard chart data. The dataset covers the top 50 songs from "The Hot 100" charts over the time period of 1960-2020, and is broken up into three different files by time period. Program has options to analyze this data in different ways.

# Program Execution:

When your program launches, the program header information will be present the user with options for files to use for the data. If the user selects a value that is not presented, the program outputs Invalid value and exits the program. Once the data is read from the file, the menu options for the different types of analysis will be displayed.

Values in the data file are separated by commas. To decipher each value separately, string functions may be used, or you may find alternative approaches that also work. See C++ documentation on string functions here: https://www.cplusplus.com/reference/string/string/. 

You will need to convert strings to numerical values for some parts of your program. The function stoi() may be helpful in doing this (see the official documentation here: https://www.cplusplus.com/reference/string/stoi/).

Some rows may have missing values for one or more columns. For instance, in the data shown at the bottom of this page, Willow by Taylor Swift has a blank value for the "last-week" column, likely because 12/26/2020 was the first week that this song appeared on the Hot 100 Billboard chart. Your program should still read in these rows, but you may need to handle these values differently.

For some of the menu options below, it asks the user to enter a decade such as 2010. However, the program should still work if the user selects 'd' for decade, and then enters a year like 2013 which is not a multiple of 10 - in this case, it would look for records from the 2010s.


# Menu Option 1 
- Display general information about the dataset that has been read in. This consists of:
The number of rows (aka size) of the dataset, and
The number of unique songs represented in the dataset

# Menu Option 2 
- Display the Billboard info of the song with the most #1 occurrences for a given decade or year. The program first prompts the user to enter the decade or year. Then, it searches within that timeframe to find all the #1 songs, and counts the number of times that these songs appeared in the #1 spot in that timeframe. The song(s) with the highest number of occurrences are displayed, with the song name and artist name printed. If there is a tie, all songs within the tie will be printed.

# Menu Option 3 
- Display the Billboard info for the most long-lasting song on the charts for a given decade or year. The program first prompts the user to enter the decade or year. Then, the program displays the song from that timeframe which has the highest number of weeks on the chart. Only 1 song is displayed.

# Menu Option 4
- Display the Billboard info for the song with the greatest weekly climb on the charts given a decade or year. The program first prompts the user to enter the decade or year. Then, the weekly climb is calculated for each record within that timeframe, and the song(s) with the greatest weekly climb is displayed. If there is a tie, all songs within the tie will be printed.

# Menu Option 5 
- Artist Search - Return the Billboard info for records that matches user input for artist search. The program prompts the user to enter a search term, and finds all records with an artist name that contains that search term (e.g. a search for "beyonce" would discover songs where Beyoncé was the main artist, or even the feature artist). This search is not case-sensitive, and will display the first 10 songs that were #1 on the charts and that match the artist name.

# Menu Option 6 
- Exit the program.


# Data Files:

The format of the comma-separated values (csv) data files is the same.  Following is the contents of the first 10 rows of charts_top50_2001_2020.csv,  followed by the same information displayed when viewed using a spreadsheet application such as Excel. The data is sorted from newest to oldest, and then by rank. Each of the data files are shown at the very bottom of this page.
