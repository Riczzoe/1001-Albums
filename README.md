# 1001 Album Recommender

This is a simple C program that selects one of the [1001 Albums You Must Hear Before You Die](https://en.wikipedia.org/wiki/1001_Albums_You_Must_Hear_Before_You_Die) and recommends it to you every day.

## Getting Started

### Prerequisites

To compile and run this program, you need to have a C compiler installed on your system.

### Usage

1. Clone the repository:
    ```
    git clone https://github.com/Riczzoe/1001-Albums.git
    ```

2. Compile the program:

   ```
   gcc main.c -o any_name_you_want
   ```

3. Run the program:

   ```
   ./any_name_you_want
   ```

   The program will display the album you should listen to for the day.

4. Enjoy your music!

## Program Details

The program uses the following files:

- `data.txt`: Stores the last date and the number of albums already listened to.
- `1001-albums.txt`: Contains the list of 1001 albums.
- `log.txt`: Keeps a log of the albums listened to each day.

### Functionality

- The program reads the last date and the number of albums already listened to from `data.txt`.
- It checks if the current date is different from the last date. If it is, the program either randomly selects a new album or increments the number of albums already listened to.
- The album information is read from `1001-albums.txt` based on the number of albums already listened to.
- The program updates the data file with the new date and album information.
- If all albums have been listened to, the program asks the user if they want to listen randomly or in the same order.
- The program logs the date and album information in `log.txt`.

## License

This project is licensed under the [MIT License](LICENSE).

