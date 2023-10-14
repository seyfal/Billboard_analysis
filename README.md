

# Billboard_analysis

Billboard_analysis is a data-driven application that offers insightful quantification and summarization of the Billboard "Hot 100" charts spanning from 1960 to 2020. Harness the power of this application to uncover fascinating trends, artist performances, and the legacy of songs over decades.

## Overview

The dataset comprises the top 50 songs from the "Hot 100" charts, distributed across three distinct time-period based files. With a user-friendly interface, you can effortlessly navigate through a suite of analysis options, each meticulously designed to unlock a unique perspective of the data.

## How It Works

1. **Initialization**: Upon launching the program, you're greeted with the header information and file options, delineating which era of songs you wish to explore. Choosing an option outside the provided range will terminate the program.

2. **Data Parsing**: The data in the files is comma-separated. Advanced string manipulation techniques are employed to dissect and interpret the data for analysis. The program gracefully handles anomalies like missing values, ensuring consistent performance.

3. **Analysis Menu**: Post data-loading, you're presented with an array of analysis choices, each catering to a different query or observation about the data.

## Analysis Options

### 1. Dataset Overview
Get a bird's eye view:
- Total rows (or dataset size).
- Distinct songs in the dataset.

### 2. Dominance of a Decade
Identify the song that reigned supreme:
- Enter a year or decade.
- Discover the song(s) that stayed the longest at #1.

### 3. Longevity Ladder
Discover songs that stood the test of time:
- Input a year or decade.
- Find out the song that lingered the longest on the charts.

### 4. Climbers of the Chart
Track the meteoric rises:
- Specify a year or decade.
- Determine the song(s) that made the most significant weekly jump.

### 5. Artist Spotlight
Shine a light on your favorite artist:
- Input an artist's name (case-insensitive).
- See their top 10 chart-topping songs.

### 6. Exit
Gracefully terminate the program.

## Data Snapshot

The application derives its insights from `.csv` files formatted consistently across the time frames. As an example, here's a glimpse of `charts_top50_2001_2020.csv` when viewed via applications like Excel: [Link to sample data or visualization].

## Getting Started

### Prerequisites
- C++ Compiler (e.g., g++)
- Familiarity with command line or terminal operations

### Installation & Execution
1. Clone the repository to your system.
```
git clone <repository_url>
```
2. Navigate to the directory with the source code.
3. Compile the source code:
```
g++ -o Billboard_analysis main.cpp
```
4. Launch the program:
```
./Billboard_analysis
```

## Final Thoughts
Billboard_analysis offers music enthusiasts, researchers, and curious minds an avenue to navigate and dissect half a century of musical history. Dive deep and uncover stories that only data can tell.
