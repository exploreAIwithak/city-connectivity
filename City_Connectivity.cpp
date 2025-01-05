#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <limits>
#include <fstream>
#include <queue>
#include <stack>
#include <functional>
#include <map>
#include <set>
#include <climits>
#include <iomanip>
#include <conio.h> 
#include <stdexcept> 

using namespace std;



// Sorting Algorithms
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

bool bruteForceStringMatch(const string& text, const string& pattern) {
    int n = text.size();       
    int m = pattern.size();    

    for (int i = 0; i <= n - m; i++) {
        int j;
       
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break; 
            }
        }
        if (j == m) {
            return true; 
        }
    }
    return false; 
}

bool subsetSum(const vector<int>& nums, int target, int index = 0, int currentSum = 0) {
    if (currentSum == target) return true;

    if (index == nums.size() || currentSum > target) return false;

    return subsetSum(nums, target, index + 1, currentSum + nums[index]) ||
           subsetSum(nums, target, index + 1, currentSum);
}

// Graph Algorithms
void dijkstra(vector<vector<pair<int, int>>>& graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, src);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "To " << i << " : " << dist[i] << "\n";
    }
}

struct Edge {
    int src, dest, weight;
};

bool compareEdge(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

int findParent(vector<int>& parent, int node) {
    if (parent[node] == -1) return node;
    return parent[node] = findParent(parent, parent[node]);
}

void unionSet(vector<int>& parent, vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);

    if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

void kruskalAlgorithm(vector<Edge>& edges, int V) {
    sort(edges.begin(), edges.end(), compareEdge);
    vector<int> parent(V, -1);
    vector<int> rank(V, 0);

    vector<Edge> mst;
    int mstWeight = 0;

    for (Edge edge : edges) {
        int u = findParent(parent, edge.src);
        int v = findParent(parent, edge.dest);

        if (u != v) {
            mst.push_back(edge);
            mstWeight += edge.weight;
            unionSet(parent, rank, u, v);
        }
    }

    cout << "Minimum Spanning Tree using Kruskal's Algorithm:\n";
    for (Edge e : mst) {
        cout << e.src << " - " << e.dest << " : " << e.weight << "\n";
    }
    cout << "Total Weight: " << mstWeight << "\n";
}

void printLine(int length, const char c)
{
    for (int i = 0; i < length; i++) {
        cout << c;
    }
    cout << endl;
}





// Data Structures for the System

// Data Structure for Room // Data Structure for Room
struct Room
{
    string roomType;
    int price;
    bool isAvailable;

    // Constructor for Room
    Room(string type, int p, bool available)
        : roomType(type), price(p), isAvailable(available) {}
};

// Data Structure for Hotel

struct Hotel
{
    string name;
    double distanceFromPlace;
    int pricePerNight;  // This value is not used, but kept for the structure's consistency
    vector<Room> rooms;
    string description;
    string contactNumber;
    double rating;  // New field for rating

    // Constructor with rating
    Hotel(string name, double distanceFromPlace, int pricePerNight, vector<Room> rooms, string description, string contactNumber, double rating)
        : name(name), distanceFromPlace(distanceFromPlace), pricePerNight(pricePerNight), rooms(rooms), description(description), contactNumber(contactNumber), rating(rating) {}
};


// Data Structure for Tourist places
struct TouristPlace
{
    string name;
    string location;
    vector<string> facilities;
    vector<Hotel> hotels;

    // Constructor for TouristPlace
    TouristPlace(string n, string loc, vector<string> fac, vector<Hotel> h)
        : name(n), location(loc), facilities(fac), hotels(h) {}
};



// Function to write booking details to detail.txt
void writeBookingToFile(const string &bookingDetails)
{
    ofstream file("detail.txt", ios::app);

    // Open in append mode
    if (!file.is_open())
    {
        cout << "Error opening file: detail.txt" << endl;
        return;
    }
    file << bookingDetails << endl;

    // Write booking details
    file.close();
}



// Function to read booking details from detail.txt
vector<string> readBookingsFromFile()
{
    vector<string> bookings;
    ifstream file("detail.txt");
    if (!file.is_open())
    {
        cout << "Error opening file: detail.txt" << endl;
        return bookings;
    }

    string line;
    while (getline(file, line))
    {
        bookings.push_back(line);

        // Read each line into the vector
    }
    file.close();
    return bookings;
}



// Function to write canceled booking details to cancel.txt
void writeCanceledToFile(const string &canceledDetails)
{
    ofstream file("cancel.txt", ios::app);

    // Open in append mode
    if (!file.is_open())
    {
        cout << "Error opening file: cancel.txt" << endl;
        return;
    }
    file << canceledDetails << endl;

    // Write canceled details
    file.close();
}


// File Handling Functions
vector<string> readFile(const string &filename)
{
    vector<string> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return data;
    }
    string line;
    while (getline (file, line)) {
        data.push_back(line);
    }
    file.close();
    return data;
}



// Function to write data to a file
void writeFile(const string &filename, const vector<string> &data)
{

    ofstream file(filename);

    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return; // Exit if the file couldn't be opened
    }

    for (const string &line : data)
    {
        file << line << endl;  // Write each line followed by a newline
    }

    // Close the file after writing is complete
    file.close();
}


// Utility Functions
void displayLine(char c = '-', int width = 58)
{
    cout << string(width, c) << endl;
}


// Display Main menu for accommodation
void displayMenu()
{
    displayLine();
    cout << "\n  Accommodation Management System \n";
    displayLine();
    cout << "1. View Tourist Places  -";
    cout << "   Discover top attractions.\n";

    cout << "2. Find Accommodation  \t-";
    cout << "   Search for unique stays.\n";

    cout << "3. Hotels by Rating  \t-";
    cout << "   View Hotels Sorted by Rating\n";

    cout << "4. Book Your Stay  \t-";
    cout << "   Reserve the perfect room.\n";

    cout << "5. Cancel Your Booking  -";
    cout << "   Modify your plans.\n";

    cout << "6. View Trip Details  \t-";
    cout << "   Check your bookings.\n";

    cout << "7. Feedback \t\t-";
    cout << "   Give Feedback.\n";

    cout << "8. Exit \t\t-";
    cout << "   Close the system.\n";
    displayLine();

    cout << "\nPlease select an option (1-7): ";
}



// Function to display canceled booking details from cancel.txt
void cancelDetails()
{
    cout << "\n";
    cout << "              Cancelled Booking Details              \n";
    cout << "==========================================================\n";
    ifstream file("cancel.txt"); // Open cancel.txt in read mode
    if (!file.is_open())
    {
        cout << "Error opening file: cancel.txt" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl; // Print the booking details (Tourist Place, Hotel, etc.)
    }

    file.close(); // Close the file after reading
}



// Booked room details
void bookingDetails()
{
    cout << "\n";
    cout << "                       Booking Details\n";
    cout << "==========================================================\n";
    vector<string> bookings = readBookingsFromFile(); // Read bookings from file

    if (!bookings.empty())
    {
        for (const auto &booking : bookings) {
            cout << booking << "\n"; // Directly displaying the booking for now
        }
    }
    else
    {
        cout << "No active bookings found.\n";
    }
}



// Function for view details of booked rooms and cancelled bookings
void viewdetails()
{
    cout << "\n==========================================================\n";
    cout << "              View Trip Details\n";
    cout << "==========================================================\n";
    cout << "\n";

    cout << "1. View Booking History\t-";
    cout << "   Check your past bookings.\n";
    cout << "2. View Cancellation History\t-";
    cout << "   Check your past cancellations.\n";

    int ch;
    cout << "\nEnter your choice : ";
    cin >> ch;

    switch(ch)
    {
        case 1:
            bookingDetails();
            break;

        case 2:
            cancelDetails();
            break;

        default:
            cout << "Invalid choice! Please select again.\n";
            break;
    }
}


// Function to display the hotels and their respective rooms and their prices
// Function to display hotel details with available rooms
void displayHotels(const vector<Hotel> &hotels)
{
    cout << "\nAccommodation Details" << endl;
    displayLine();  // Assuming displayLine is a helper function that formats output

    // Loop through all hotels to display their details
    for (size_t i = 0; i < hotels.size(); i++)
    {
        // Display basic hotel details
        cout << i + 1 << ". " << hotels[i].name << endl;
        cout << "   Distance: " << hotels[i].distanceFromPlace << " km" << endl;  // Distance from the tourist place
        cout << "   Price per night: Rs. " << hotels[i].pricePerNight << endl;
        cout << "   Rating: " << hotels[i].rating << " stars" << endl;  // Rating of the hotel
        cout << "   Description: " << hotels[i].description << endl;  // Short description of the hotel
        cout << "   Contact: " << hotels[i].contactNumber << endl;  // Contact number of the hotel
        cout << "   Available Rooms:" << endl;

        // Display room details in a formatted manner
        cout << "       Room Type         Price          Availability" << endl;
        displayLine();  // Assuming displayLine is used to separate sections visually

        // Loop through rooms and display availability
        for (const auto &room : hotels[i].rooms)
        {
            cout << "       " << setw(15) << room.roomType << "  "
                 << "Rs. " << setw(10) << room.price << "  "
                 << (room.isAvailable ? "Available" : "Booked") << endl;
        }
        cout << endl;  // Add extra space between hotels for clarity
    }
}




// Function to book room and update the hotel details
void bookRoom(vector<TouristPlace> &places)
{
    // Display the booking menu header
    cout << "\n=====================================================\n";
    cout << "                     Book a Room\n";
    cout << "=====================================================\n";

    // Display the list of available tourist places
    cout << "\nAvailable Tourist Places:\n";

    for (size_t i = 0; i < places.size(); ++i)
    {
        cout << i + 1 << ". " << places[i].name << " (" << places[i].location << ")\n";
    }

    // Prompt user to select a tourist place
    cout << "\nEnter the tourist place : ";
    int placeChoice;

    // Input validation for tourist place choice
    while (!(cin >> placeChoice) || placeChoice < 1 || placeChoice > places.size())
    {
        cout << "\nInvalid input! \nPlease enter a valid tourist place number : ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Discard invalid input
    }

    // Display the list of hotels in the selected tourist place
    cout << "\nAvailable Hotels:\n";

    for (size_t i = 0; i < places[placeChoice - 1].hotels.size(); ++i)
    {
        // Display hotel details (name and distance from the tourist place)
        cout << i + 1 << ". " << places[placeChoice - 1].hotels[i].name << "\t"
             << " (" << places[placeChoice - 1].hotels[i].distanceFromPlace << " km away)\n";
    }

    // Prompt user to select a hotel
    cout << "\nEnter the hotel number to book a room : ";
    int hotelChoice;

    // Input validation for hotel choice
    while (!(cin >> hotelChoice) || hotelChoice < 1 || hotelChoice > places[placeChoice - 1].hotels.size())
    {
        cout << "\nInvalid input! \nPlease enter a valid hotel number : ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Discard invalid input
    }

    // Get the selected hotel
    Hotel &selectedHotel = places[placeChoice - 1].hotels[hotelChoice - 1];

    // Display the selected hotel and its available rooms
    cout << "\n=====================================================\n";
    cout << "      Selected Hotel: " << selectedHotel.name << "\n";
    cout << "=====================================================\n";

    cout << "\nAvailable Rooms:\n";
    bool roomAvailable = false;
    // Check if at least one room is available

    // Display available rooms in the selected hotel
    for (size_t i = 0; i < selectedHotel.rooms.size(); ++i)
    {
        if (selectedHotel.rooms[i].isAvailable)
        {
            roomAvailable = true;
            cout << i + 1 << ". " << selectedHotel.rooms[i].roomType
                 << " - Rs. " << selectedHotel.rooms[i].price << "\n";
        }
    }

    // If no rooms are available, notify the user and return
    if (!roomAvailable)
    {
        cout << "\nNo rooms are available in " << selectedHotel.name << ".\n";
        cout << "Returning to the main menu...\n";
        return;
    }

    // Prompt user to select a room
    cout << "\nEnter the room number to book : ";
    int roomChoice;

    // Input validation for room choice
    while (!(cin >> roomChoice) || roomChoice < 1 || roomChoice > selectedHotel.rooms.size() || !selectedHotel.rooms[roomChoice - 1].isAvailable)
    {
        cout << "\nInvalid room choice or the room is already booked! \nPlease enter a valid room number : ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Discard invalid input
    }

    // Display confirmation message for the selected room
    cout << "\nYou have selected:\n";
    cout << "Room Type: " << selectedHotel.rooms[roomChoice - 1].roomType << "\n";
    cout << "Price: Rs. " << selectedHotel.rooms[roomChoice - 1].price << "\n";
    cout << "Hotel: " << selectedHotel.name << "\n";
    cout << "-----------------------------------------------------\n";
    cout << "Confirm booking? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    // Normalize user input to lowercase
    transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::tolower);

    // Process booking confirmation
    if (confirmation == "yes")
    {
        // Ask for payment method
        cout << "How would you like to pay?(cash/upi) : ";
        string paymentMethod;
        cin >> paymentMethod;

        // Normalize payment method input
        transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(), ::tolower);

        if (paymentMethod == "cash" || paymentMethod == "upi")
        {
            // Mark room as booked
            selectedHotel.rooms[roomChoice - 1].isAvailable = false;
            cout << "\n=====================================================\n";
            cout << "  Payment of Rs. " << selectedHotel.rooms[roomChoice - 1].price
                 << " received via " << paymentMethod << ".\n";
            cout << "  Room booked successfully at " << selectedHotel.name << "!\n";
            cout << "=====================================================\n";

            // Save booking details to file
            string bookingDetails = "Booking Confirmation\n" +
                                    string("==============================\n") +
                                    "Tourist Place: " + places[placeChoice - 1].name + "\n" +
                                    "Hotel: " + selectedHotel.name + "\n" +
                                    "Room Type: " + selectedHotel.rooms[roomChoice - 1].roomType + "\n" +
                                    "Price: Rs. " + to_string(selectedHotel.rooms[roomChoice - 1].price) + "\n" +
                                    "Payment Method: " + paymentMethod + "\n" +
                                    string("==============================\n");

            writeBookingToFile(bookingDetails); // Save booking details to file
        }

        else
        {
            cout << "\nInvalid payment method! Booking process aborted.\n";
        }
    }

    else
    {
        cout << "\nBooking process aborted. Returning to the main menu...\n";
    }
}



// Function to display tourist places and their hotels
void displayTouristPlaces(const vector<TouristPlace> &places)
{
    cout << "\nExplore the Beauty of Mysuru - Tourist Places" << endl;
    displayLine();

    for (size_t i = 0; i < places.size(); i++) {
        cout << i + 1 << ". " << places[i].name << endl;
    }
    displayLine();

    cout << "Choose a place to explore (1-" << places.size() << "): ";
}



// Function to display hotel names for the selected tourist place
void displayHotelNames(const TouristPlace &place)
{
    // Display the header with the name of the selected tourist place
    cout << "\nHotels near " << place.name << ":" << endl;

    // Loop through each hotel in the tourist place and display its name
    for (size_t i = 0; i < place.hotels.size(); i++)
    {
        // Display hotel number (1-based) and hotel name
        cout << i + 1 << ". " << place.hotels[i].name << endl;
    }

    // Prompt the user to choose a hotel by number
    cout << "\nChoose a hotel (1-" << place.hotels.size() << "): ";
}





// Function to display details of the selected hotel
// Function to display details of a selected hotel
void displaySelectedHotelDetails(const Hotel &hotel)
{
    // Display the hotel header and name
    cout << "\n==========================================================\n";
    cout << "Hotel Details: " << hotel.name << endl;
    cout << "==========================================================\n";

    // Display location details
    cout << "Location Details:\n";
    cout << "  Distance from tourist place: " << hotel.distanceFromPlace << " km\n";
    cout << "  Price per night:             Rs. " << hotel.pricePerNight << endl;
    cout << "  Rating:                     " << hotel.rating << " stars" << endl;
    // Added rating
    cout << "  Description:\n    " << hotel.description << endl;
    cout << "  Contact Information:         " << hotel.contactNumber << endl;
     // Fixed typo 'contact' to 'contactNumber'

    // Function to display a separator line
    displayLine();

    // Display room availability section
    cout << "Room Availability:\n";
    // Set column widths for better alignment of room details
    cout << setw(15) << "Room Type";
    cout << setw(20);
    cout << "Price per Night" ;
    cout << setw(20);
    cout << "Availability";
    cout << endl;

    // Function to display a separator line
    displayLine();

    // Loop through each room in the hotel and display its details
    for (const auto &room : hotel.rooms)
    {
        // Display room type, price, and availability status
        cout << setw(15) << room.roomType
             << setw(20) << "Rs. " + to_string(room.price)
             << setw(20) << (room.isAvailable ? "Available" : "Booked") << endl;
    }

    // Display a separator line at the end
    displayLine();
}



// Function to search for accommodation based on
// user's preferences and display the results
void searchAccommodation(const vector<TouristPlace> &places)

{
    // Prompt the user to enter the name of the hotel they are searching for
    cout << "\nEnter the name of the hotel to search: ";
    string searchQuery;

    cin.ignore();  // Ignore any leftover newline characters
    getline(cin, searchQuery);  // Get the full line input from the user

    // Convert the search query to lowercase for case-insensitive comparison
    transform(searchQuery.begin(), searchQuery.end(), searchQuery.begin(), ::tolower);

    bool found = false;  // Flag to track whether any matching hotels are found

    // Loop through all the tourist places
    for (const auto &place : places)
    {
        // Loop through all the hotels in the current place
        for (const auto &hotel : place.hotels)
        {
            // Convert the hotel name to lowercase for comparison
            string hotelNameLower = hotel.name;
            transform(hotelNameLower.begin(), hotelNameLower.end(), hotelNameLower.begin(), ::tolower);

            // Check if the lowercase hotel name contains the search query
            if (hotelNameLower.find(searchQuery) != string::npos)
            {
                // If a match is found, display the hotel and the associated tourist place
                cout << "Found: " << hotel.name << " near " << place.name << endl;
                found = true;
            }
        }
    }

    // If no matching accommodation was found, display a message
    if (!found) {
        cout << "\nNo accommodation found with the name: " << searchQuery << endl;
    }
}




// Function to cancel a booking
void cancelBooking(vector<TouristPlace>& places)

{
    // Display a separator and the cancel booking title
    cout << "\n=====================================================\n";
    cout << "              Cancel a Booking\n";
    cout << "=====================================================\n";

    // Read the bookings from the "detail.txt" file
    vector<string> bookings = readBookingsFromFile();

    // If there are no bookings
    if (bookings.empty())
    {
        cout << "\nNo bookings found! You don't have any rooms booked.\n";
        return;
    }

    // Display the list of bookings with indexing every 8 lines
    cout << "\nYour Bookings:\n";
    int bookingIndex = 1;

    for (size_t i = 0; i < bookings.size(); i += 8)
    {
        // Step 8 because each booking is 8 lines
        cout << "Booking " << bookingIndex++ << ":\n";

        for (size_t j = i; j < i + 8 && j < bookings.size(); ++j) {

            cout << bookings[j] << endl;
        }
        cout << "\n";
        // Add a blank line between different bookings
    }

    // Prompt user to select a booking to cancel
    cout << "\nEnter the booking number to cancel (1-" << (bookingIndex - 1) << ") : ";
    int bookingChoice;

    // Input loop to ensure a valid booking number is selected
    while (!(cin >> bookingChoice) || bookingChoice < 1 || bookingChoice >= bookingIndex)
    {
        cout << "\nInvalid input! Please enter a valid booking number : ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Discard invalid input
    }

    // Calculate the starting index of the selected booking in the bookings vector
    int bookingStartIndex = (bookingChoice - 1) * 8;

    // Extract the canceled booking details
    string canceledBookingDetails = "";
    for (int i = bookingStartIndex; i < bookingStartIndex + 8 && i < bookings.size(); ++i)
    {
        canceledBookingDetails += bookings[i] + "\n";
    }

    // Extract relevant booking details from the canceled booking (e.g., Tourist Place, Hotel, Room)
    size_t touristPlaceStart = canceledBookingDetails.find("Tourist Place: ") + 15;
    size_t hotelStart = canceledBookingDetails.find("Hotel: ") + 7;
    size_t roomStart = canceledBookingDetails.find("Room Type: ") + 11;
    size_t priceStart = canceledBookingDetails.find("Price: Rs. ") + 11;

    // Get the specific details (Tourist Place, Hotel, Room Type, Price) from the booking
    string touristPlaceName = canceledBookingDetails.substr(touristPlaceStart, canceledBookingDetails.find("\n", touristPlaceStart) - touristPlaceStart);
    string hotelName = canceledBookingDetails.substr(hotelStart, canceledBookingDetails.find("\n", hotelStart) - hotelStart);
    string roomType = canceledBookingDetails.substr(roomStart, canceledBookingDetails.find("\n", roomStart) - roomStart);
    string price = canceledBookingDetails.substr(priceStart, canceledBookingDetails.find("\n", priceStart) - priceStart);

    // Find the booking details in the places vector and set the room availability back to true
    bool roomFound = false;
    for (auto &place : places)
    {
        for (auto &hotel : place.hotels)
        {
            if (hotel.name == hotelName)
            {
                for (auto &room : hotel.rooms)
                {
                    if (room.roomType == roomType && !room.isAvailable)
                    {
                        room.isAvailable = true;
                        roomFound = true;
                        break;
                    }
                }
            }
            if (roomFound) break;
        }
        if (roomFound) break;
    }

    // If the room was found and successfully marked as available
    if (roomFound) {
        // Display confirmation that the booking has been canceled and the room is available
        cout << "\n=====================================================";
        cout << "\n";
        cout << "  The booking for room type '" << roomType << "' at " << hotelName << " has been canceled.";
        cout << "\n";
        cout << "  The room is now available for booking again.";
        cout << "\n";
        cout << "=====================================================";
        cout << "\n";

        // Save canceled booking details to cancel.txt
        string canceledDetails = string("==============================\n") +
                                 "Canceled Booking Details\n" +
                                 string("==============================\n") +
                                 "Tourist Place: " + touristPlaceName + "\n" +
                                 "Hotel: " + hotelName + "\n" +
                                 "Room Type: " + roomType + "\n" +
                                 "Price: Rs. " + price + "\n" +
                                 string("==============================\n");

        writeCanceledToFile(canceledDetails);
        // Save canceled booking details to file

        // Remove the canceled booking from the bookings list
        bookings.erase(bookings.begin() + bookingStartIndex, bookings.begin() + bookingStartIndex + 8);

        // Write the updated bookings list back to the detail.txt file
        writeFile("detail.txt", bookings);
        // Correct function to rewrite the full list
    }
    else
    {
        // Display an error if the booking was not found or the room was already available
        cout << "\nError: Booking not found or room was already available!";
        cout << "\n";
    }
}




// Function to collect feedback from the user
void collectFeedback()

{
    // Declare variables to store feedback text and rating
    string feedbackText;
    int rating;

    // Print a separator line and prompt for feedback text
    cout << "\n============================== FeedBACK ==============================" << endl;
    cout << "We value your feedback! Please share your thoughts about our service:" << endl;
    cout << "-----------------------------------------------------------------------" << endl;

    // Prompt the user to enter their feedback
    cout << "Enter your feedback: ";

    // Clear the input buffer before taking the input
    cin.ignore();

    // Get the full line of feedback text
    getline(cin, feedbackText);

    // Prompt for a rating from 1 to 5
    cout << "Please rate your experience from 1 to 5 \n(1 being the lowest and 5 being the highest): ";

    // Read the rating input
    cin >> rating;

    // Validate the rating input to ensure it's between 1 and 5
    while (rating < 1 || rating > 5)
    {
        cout << "Invalid rating! Please enter a number between 1 and 5: ";
        cin >> rating;
    }

    // Print a separator line after the rating input
    cout << "-----------------------------------------------------------------------" << endl;

    // Thank the user for their feedback
    cout << "Thank you for your feedback!" << endl;

    // Respond based on the rating provided by the user
    switch (rating)
    {
        case 1:
            cout << "\nWe're sorry to hear that you had a poor experience. \nWe will strive to improve!" << endl;
            break;

        case 2:
            cout << "\nWe appreciate your input and will work on making things better." << endl;
            break;

        case 3:
            cout << "\nWe're glad you had an average experience, \nbut we aim to do better." << endl;
            break;

        case 4:
            cout << "\nWe're happy to hear you had a good experience. \nYour feedback motivates us!" << endl;
            break;

        case 5:
            cout << "\nWe're thrilled you had an excellent experience!" << endl;
            break;
    }

    // Open a file in append mode to save the feedback
    ofstream feedbackFile("feedback.txt", ios::app); // Open file in append mode

    // Check if the file was opened successfully
    if (feedbackFile.is_open())
    {
        // Write feedback details to the file
        feedbackFile << "Accommodation Management System Feedback:" << endl;
        feedbackFile << "Feedback: " << feedbackText << endl;
        feedbackFile << "Rating: " << rating << endl;
        feedbackFile << "---------------------------------------------------" << endl;

        // Close the file after writing
        feedbackFile.close();
        cout << "Your feedback has been saved successfully!" << endl;
    }
    else
    {
        // Print an error message if unable to open the file
        cout << "Error: Unable to save feedback to file." << endl;
    }

    // Display a closing message thanking the user for their feedback
    cout << "\nYour feedback is important to us, \nand we will use it to enhance our services." << endl;
    cout << "=======================================================================" << endl;

}




// Thank you function contains the statements for thanking
// Function to display the thank you message to the user
void thankyou()

{
    // Print a separator line for clarity
    cout << "\n=========================================================";

    // Print a blank line for spacing
    cout << "\n";

    // Print the first part of the thank you message
    cout << "             Thank You for Choosing Mysuru's";

    // Print a blank line after the first message
    cout << "\n";

    // Print the second part of the thank you message
    cout << "       Accommodation Management System for Your Stay";

    // Print a blank line after the second message
    cout << "\n";

    // Print the final part of the thank you message
    cout << "   We look forward to welcoming you back in the future!";

    // Print the closing separator line
    cout << "\n=========================================================";

    // Print a couple of blank lines for extra spacing
    cout << "\n";
    cout << "\n";
}




// Function to display the welcome message to the user
void displayWelcomeMessage()

{
    // Print a separator line for clarity
    cout << "\n=========================================================\n";

    // Print the welcome message
    cout << "     Welcome to the Karnataka Tourism Management System!\n";

    // Print the tagline for the system
    cout << "        Your Trusted Partner for Travel and Stays         \n";

    // Print the closing separator line
    cout << "=========================================================\n";
}



// Function to handle tourist place selection
// Function to handle the selection of a tourist place and hotel
void handleTouristPlaceSelection(const vector<TouristPlace>& places) {

    // Display the list of tourist places
    displayTouristPlaces(places);

    // Variable to store the user's choice of tourist place
    int placeChoice;

    // Input loop for valid tourist place selection
    while (!(cin >> placeChoice) || placeChoice < 1 || placeChoice > places.size()) {
        // Prompt the user to enter a valid place number if the input is invalid
        cout << "Invalid place selection! Please enter a valid number: ";

        // Clear the error flag and ignore invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Display the list of hotels for the selected tourist place
    displayHotelNames(places[placeChoice - 1]);

    // Variable to store the user's choice of hotel
    int hotelChoice;

    // Input loop for valid hotel selection
    while (!(cin >> hotelChoice) || hotelChoice < 1 || hotelChoice > places[placeChoice - 1].hotels.size()) {
        // Prompt the user to enter a valid hotel number if the input is invalid
        cout << "Invalid hotel selection! Please enter a valid number: ";

        // Clear the error flag and ignore invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Display the details of the selected hotel
    displaySelectedHotelDetails(places[placeChoice - 1].hotels[hotelChoice - 1]);
}





// Function to handle booking
void bookRoom(Hotel& selectedHotel)
{
    // Display available rooms in the selected hotel
    cout << "\n=====================================================\n";
    cout << "      Selected Hotel: " << selectedHotel.name << "\n";
    cout << "=====================================================\n";

    cout << "\nAvailable Rooms:\n";
    bool roomAvailable = false;
    for (size_t i = 0; i < selectedHotel.rooms.size(); ++i)
    {
        //  Display room details
        if (selectedHotel.rooms[i].isAvailable)
        {
            //  Display room details
            roomAvailable = true;
            cout << i + 1 << ". " << selectedHotel.rooms[i].roomType
                 << " - Rs. " << selectedHotel.rooms[i].price << "\n";
        }
    }

    if (!roomAvailable)
    {
        //  Display message if no rooms are available
        cout << "\nNo rooms are available in " << selectedHotel.name << ".\n";
        return;
    }

    // Prompt user to select a room
    cout << "\nEnter the room number to book: ";
    int roomChoice;
    cin >> roomChoice;

    while (roomChoice < 1 || roomChoice > selectedHotel.rooms.size() || !selectedHotel.rooms[roomChoice - 1].isAvailable)
    {
        //  Clear input buffer if invalid input
        cout << "\nInvalid room choice or the room is already booked! Please enter a valid room number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> roomChoice;
    }

    // Display confirmation message
    cout << "\nYou have selected:\n";
    cout << "Room Type: " << selectedHotel.rooms[roomChoice - 1].roomType << "\n";
    cout << "Price: Rs. " << selectedHotel.rooms[roomChoice - 1].price << "\n";
    cout << "Hotel: " << selectedHotel.name << "\n";
    cout << "-----------------------------------------------------\n";
    cout << "Confirm booking? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    // Normalize user input to lowercase
    transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::tolower);

    // Process confirmation
    if (confirmation == "yes")
    {
        //  Update room status
        // Ask for payment method
        cout << "How would you like to pay? (cash/upi): ";
        string paymentMethod;
        cin >> paymentMethod;

        // Normalize payment method input
        transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(), ::tolower);

        if (paymentMethod == "cash" || paymentMethod == "upi")
        {
            //  Update room status
            selectedHotel.rooms[roomChoice - 1].isAvailable = false;
            cout << "\n=====================================================\n";
            cout << "  Payment of Rs. " << selectedHotel.rooms[roomChoice - 1].price
                 << " received via " << paymentMethod << ".\n";
            cout << "  Room booked successfully at " << selectedHotel.name << "!\n";
            cout << "=====================================================\n";

            // Save comprehensive booking details to file
            string bookingDetails = "Booking Confirmation\n" +
                                    string("==============================\n") +
                                    "Hotel: " + selectedHotel.name + "\n" +
                                    "Room Type: " + selectedHotel.rooms[roomChoice - 1].roomType + "\n" +
                                    "Price: Rs. " + to_string(selectedHotel.rooms[roomChoice - 1].price) + "\n" +
                                    "Payment Method: " + paymentMethod + "\n" +
                                    string("==============================\n");

            // Assuming writeBookingToFile function exists
            writeBookingToFile(bookingDetails); // Save booking details to file
        }
        else
        {
            //  Update room status
            cout << "\nInvalid payment method! Booking process aborted.\n";
        }
    }
    else
    {
        //  Update room status
        cout << "\nBooking process aborted. Returning to the main menu...\n";
    }
}




// Main function for displaying hotels by
// tourist place and handling user selection
void displayHotelsByRating(vector<TouristPlace>& places)
{
    //  Display tourist places
    // Ask user to select a tourist place
    cout << "\nSelect a Tourist Place:\n";

    displayLine();

    for (size_t i = 0; i < places.size(); ++i)
    {
        //  Display tourist places
        cout << i + 1 << ". " << places[i].name << "\n";
    }
    cout << "\nEnter the tourist place number : ";
    int placeChoice;
    cin >> placeChoice;

    while (placeChoice < 1 || placeChoice > places.size())
    {
        //  Input validation
        cout << "\nInvalid input! \nPlease enter a valid tourist place number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> placeChoice;
    }

    TouristPlace& selectedPlace = places[placeChoice - 1];

    cout << "\nPlease choose a hotel category:\n";
    displayLine();
    cout << "1. Premium (Rating: 4.5 and above)\n";
    cout << "2. Standard (Rating: 3.5 to 4.5)\n";
    cout << "3. Budget (Rating below: 3.5)\n";
    cout << "\nEnter your choice: ";

    int choice;
    cin >> choice;

    vector<Hotel> premiumHotels;
    vector<Hotel> standardHotels;
    vector<Hotel> budgetHotels;

    // Categorize hotels based on rating
    for (const auto& hotel : selectedPlace.hotels)
    {
        //  Assuming hotel.rating is a float value
        // between 0 and 5
        if (hotel.rating >= 4.5)
        {
            //  Add to premium hotels list
            premiumHotels.push_back(hotel);
        }
        else if (hotel.rating >= 3.5)
        {
            //  Add to standard hotels list
            standardHotels.push_back(hotel);
        }
        else
        {
            //   Add to budget hotels list
            budgetHotels.push_back(hotel);
        }
    }

    switch (choice) {
        case 1: {
            // Premium hotels
            if (premiumHotels.empty())
            {
                //  Display message if no premium hotels found
                cout << "\nNo Premium hotels are available for booking.\n";
                break;
            }

            cout << "\nPremium Hotels:\n";
            for (size_t i = 0; i < premiumHotels.size(); ++i)
            {
                //  Display hotel details
                cout << i + 1 << ". " << premiumHotels[i].name;
                cout << " \t(Rating: " << premiumHotels[i].rating << ")"<< "\n";
            }

            // Ask the user if they want to book a room
            cout << "\nWould you like to book a room? (yes/no): ";
            string bookChoice;
            cin >> bookChoice;
            transform(bookChoice.begin(), bookChoice.end(), bookChoice.begin(), ::tolower);

            if (bookChoice == "yes") {
                // Ask the user to choose a hotel to book

                cout << "\nProceeding to Booking...\n";
                cout << "\nEnter the hotel number to book a room : ";
                int hotelChoice;
                cin >> hotelChoice;

                while (hotelChoice < 1 || hotelChoice > premiumHotels.size())
                {
                    //  Input validation
                    cout << "\nInvalid input! \nPlease enter a valid hotel number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> hotelChoice;
                }

                Hotel& selectedHotel = premiumHotels[hotelChoice - 1];
                // Display available rooms in the selected hotel
    cout << "\n=====================================================\n";
    cout << "      Selected Hotel: " << selectedHotel.name << "\n";
    cout << "=====================================================\n";

    cout << "\nAvailable Rooms:\n";
    bool roomAvailable = false;
    for (size_t i = 0; i < selectedHotel.rooms.size(); ++i)
    {
        //  Check if the room is available

        if (selectedHotel.rooms[i].isAvailable)
        {
            //  Check if the room is available

            roomAvailable = true;
            cout << i + 1 << ". " << selectedHotel.rooms[i].roomType
                 << " - Rs. " << selectedHotel.rooms[i].price << "\n";
        }
    }

    if (!roomAvailable)
    {
        //  Check if the room is available

        cout << "\nNo rooms are available in " << selectedHotel.name << ".\n";
        return;
    }

    // Prompt user to select a room
    cout << "\nEnter the room number to book : ";
    int roomChoice;
    cin >> roomChoice;

    while (roomChoice < 1 || roomChoice > selectedHotel.rooms.size() || !selectedHotel.rooms[roomChoice - 1].isAvailable)
    {
        //  Input validation
        cout << "\nInvalid room choice or the room is already booked! Please enter a valid room number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> roomChoice;
    }

    // Display confirmation message
    cout << "\nYou have selected:\n";
    cout << "Room Type: " << selectedHotel.rooms[roomChoice - 1].roomType << "\n";
    cout << "Price: Rs. " << selectedHotel.rooms[roomChoice - 1].price << "\n";
    cout << "Hotel: " << selectedHotel.name << "\n";
    cout << "Tourist Place: " << selectedPlace.name << "\n";
    cout << "-----------------------------------------------------\n";
    cout << "Confirm booking? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    // Normalize user input to lowercase
    transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::tolower);

    // Process confirmation

    if (confirmation == "yes")
    {
        //  Update room status
        // Ask for payment method
        cout << "How would you like to pay? (cash/upi): ";
        string paymentMethod;
        cin >> paymentMethod;

        // Normalize payment method input
        transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(), ::tolower);

        if (paymentMethod == "cash" || paymentMethod == "upi")
        {
            //  Process payment
            selectedHotel.rooms[roomChoice - 1].isAvailable = false;

            cout << "\n=====================================================\n";
            cout << "  Payment of Rs. " << selectedHotel.rooms[roomChoice - 1].price
                 << " received via " << paymentMethod << ".\n";
            cout << "  Room booked successfully at " << selectedHotel.name << "!\n";
            cout << "=====================================================\n";

            // Save comprehensive booking details to file

            string bookingDetails = "Booking Confirmation\n" +
                                    string("==============================\n") +
                                    "Tourist Place: " + selectedPlace.name + "\n" +
                                    "Hotel: " + selectedHotel.name + "\n" +
                                    "Room Type: " + selectedHotel.rooms[roomChoice - 1].roomType + "\n" +
                                    "Price: Rs. " + to_string(selectedHotel.rooms[roomChoice - 1].price) + "\n" +
                                    "Payment Method: " + paymentMethod + "\n" +
                                    string("==============================\n");

            // Write to file

            ofstream outFile("booking_details.txt", ios::app); // Open the file in append mode
            outFile << bookingDetails << endl;
            outFile.close();
        }

        else
        {
            //  Process payment
            cout << "\nInvalid payment method! Booking process aborted.\n";
        }
    }

    else
    {
        //  Process payment
        cout << "\nBooking process aborted. Returning to the main menu...\n";
    }
            }
            else {
                cout << "\nExiting to the main menu...\n";
            }
            break;
        }

        case 2: {
            // Standard hotels
            if (standardHotels.empty())
            {
                //  If no standard hotels are available,
                // display a message and break the switch
                cout << "\nNo Standard hotels are available for booking.\n";
                break;
            }

            cout << "\nStandard Hotels:\n";
            for (size_t i = 0; i < standardHotels.size(); ++i)
            {
                //  Display the hotel name and rating
                cout << i + 1 << ". " << standardHotels[i].name;
                cout << " \t(Rating: " << standardHotels[i].rating << ")"<< "\n";
            }

            // Ask the user if they want to book a room
            cout << "\nWould you like to book a room? (yes/no): ";
            string bookChoice;

            cin >> bookChoice;
            transform(bookChoice.begin(), bookChoice.end(), bookChoice.begin(), ::tolower);

            if (bookChoice == "yes") {
                // Ask the user to choose a hotel to book

                cout << "\nProceeding to Booking...\n";
                cout << "\nEnter the hotel number to book a room : ";
                int hotelChoice;
                cin >> hotelChoice;

                while (hotelChoice < 1 || hotelChoice > standardHotels.size())
                {
                    //  Clear the input buffer to handle invalid inputs
                    cout << "\nInvalid input! \nPlease enter a valid hotel number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> hotelChoice;
                }

                Hotel& selectedHotel = standardHotels[hotelChoice - 1];
                // Display available rooms in the selected hotel
    cout << "\n=====================================================\n";
    cout << "      Selected Hotel: " << selectedHotel.name << "\n";
    cout << "=====================================================\n";

    cout << "\nAvailable Rooms:\n";
    bool roomAvailable = false;
    for (size_t i = 0; i < selectedHotel.rooms.size(); ++i)
    {
        //  Check if the room is available

        if (selectedHotel.rooms[i].isAvailable)
        {
            //  Check if the room is available

            roomAvailable = true;

            cout << i + 1 << ". " << selectedHotel.rooms[i].roomType
                 << " - Rs. " << selectedHotel.rooms[i].price << "\n";
        }
    }

    if (!roomAvailable)
    {
        //  Check if the room is available

        cout << "\nNo rooms are available in " << selectedHotel.name << ".\n";
        return;
    }

    // Prompt user to select a room
    cout << "\nEnter the room number to book : ";

    int roomChoice;
    cin >> roomChoice;

    while (roomChoice < 1 || roomChoice > selectedHotel.rooms.size() || !selectedHotel.rooms[roomChoice - 1].isAvailable)
    {
        //  Input validation
        cout << "\nInvalid room choice or the room is already booked! Please enter a valid room number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> roomChoice;
    }

    // Display confirmation message
    cout << "\nYou have selected:\n";
    cout << "Room Type: " << selectedHotel.rooms[roomChoice - 1].roomType << "\n";
    cout << "Price: Rs. " << selectedHotel.rooms[roomChoice - 1].price << "\n";
    cout << "Hotel: " << selectedHotel.name << "\n";
    cout << "Tourist Place: " << selectedPlace.name << "\n";
    cout << "-----------------------------------------------------\n";
    cout << "Confirm booking? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    // Normalize user input to lowercase
    transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::tolower);

    // Process confirmation
    if (confirmation == "yes")
    {
        //  Update room status
        // Ask for payment method
        cout << "How would you like to pay? (cash/upi): ";
        string paymentMethod;
        cin >> paymentMethod;

        // Normalize payment method input
        transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(), ::tolower);

        if (paymentMethod == "cash" || paymentMethod == "upi")
        {
            //  Process payment
            selectedHotel.rooms[roomChoice - 1].isAvailable = false;
            cout << "\n=====================================================\n";
            cout << "  Payment of Rs. " << selectedHotel.rooms[roomChoice - 1].price
                 << " received via " << paymentMethod << ".\n";
            cout << "  Room booked successfully at " << selectedHotel.name << "!\n";
            cout << "=====================================================\n";

            // Save comprehensive booking details to file
            string bookingDetails = "Booking Confirmation\n" +
                                    string("==============================\n") +
                                    "Tourist Place: " + selectedPlace.name + "\n" +
                                    "Hotel: " + selectedHotel.name + "\n" +
                                    "Room Type: " + selectedHotel.rooms[roomChoice - 1].roomType + "\n" +
                                    "Price: Rs. " + to_string(selectedHotel.rooms[roomChoice - 1].price) + "\n" +
                                    "Payment Method: " + paymentMethod + "\n" +
                                    string("==============================\n");

            // Write to file
            ofstream outFile("booking_details.txt", ios::app); // Open the file in append mode
            outFile << bookingDetails << endl;
            outFile.close();
        }
        else
        {
            //  Process payment
            cout << "\nInvalid payment method! Booking process aborted.\n";
        }
    }
    else
    {
        //  Process payment
        cout << "\nBooking process aborted. Returning to the main menu...\n";
    }
            }
            else
            {
                cout << "\nExiting to the main menu...\n";
            }
            break;
        }

        case 3: { // Budget hotels
            if (budgetHotels.empty())
            {
                cout << "\nNo Budget hotels are available for booking.\n";
                break;
            }

            cout << "\nBudget Hotels:\n";
            for (size_t i = 0; i < budgetHotels.size(); ++i) {
                cout << i + 1 << ". " << budgetHotels[i].name;
                cout << " \t(Rating: " << budgetHotels[i].rating << ")"<< "\n";
            }

            // Ask the user if they want to book a room
            cout << "\nWould you like to book a room? (yes/no): ";
            string bookChoice;
            cin >> bookChoice;
            transform(bookChoice.begin(), bookChoice.end(), bookChoice.begin(), ::tolower);

            if (bookChoice == "yes") {
                // Ask the user to choose a hotel to book

                cout << "\nProceeding to Booking...\n";
                cout << "\nEnter the hotel number to book a room : ";
                int hotelChoice;
                cin >> hotelChoice;

                while (hotelChoice < 1 || hotelChoice > budgetHotels.size())
                {
                    cout << "\nInvalid input! \nPlease enter a valid hotel number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> hotelChoice;
                }

                Hotel& selectedHotel = budgetHotels[hotelChoice - 1];
                // Display available rooms in the selected hotel
    cout << "\n=====================================================\n";
    cout << "      Selected Hotel: " << selectedHotel.name << "\n";
    cout << "=====================================================\n";

    cout << "\nAvailable Rooms:\n";
    bool roomAvailable = false;
    for (size_t i = 0; i < selectedHotel.rooms.size(); ++i)
    {
        //  Check if the room is available

        if (selectedHotel.rooms[i].isAvailable)
        {
            //  Check if the room is available

            roomAvailable = true;
            cout << i + 1 << ". " << selectedHotel.rooms[i].roomType
                 << " - Rs. " << selectedHotel.rooms[i].price << "\n";
        }
    }

    if (!roomAvailable)
    {
        //  Check if the room is available

        cout << "\nNo rooms are available in " << selectedHotel.name << ".\n";
        return;
    }

    // Prompt user to select a room

    cout << "\nEnter the room number to book : ";
    int roomChoice;
    cin >> roomChoice;

    while (roomChoice < 1 || roomChoice > selectedHotel.rooms.size() || !selectedHotel.rooms[roomChoice - 1].isAvailable)
    {
        //  Input validation
        cout << "\nInvalid room choice or the room is already booked! Please enter a valid room number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> roomChoice;
    }

    // Display confirmation message

    cout << "\nYou have selected:\n";
    cout << "Room Type: " << selectedHotel.rooms[roomChoice - 1].roomType << "\n";
    cout << "Price: Rs. " << selectedHotel.rooms[roomChoice - 1].price << "\n";
    cout << "Hotel: " << selectedHotel.name << "\n";
    cout << "Tourist Place: " << selectedPlace.name << "\n";
    cout << "-----------------------------------------------------\n";
    cout << "Confirm booking? (yes/no): ";
    string confirmation;
    cin >> confirmation;

    // Normalize user input to lowercase
    transform(confirmation.begin(), confirmation.end(), confirmation.begin(), ::tolower);

    // Process confirmation
    if (confirmation == "yes")
    {

        //  Update room status
        // Ask for payment method
        cout << "How would you like to pay? (cash/upi): ";
        string paymentMethod;
        cin >> paymentMethod;

        // Normalize payment method input
        transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(), ::tolower);


        if (paymentMethod == "cash" || paymentMethod == "upi")
        {
            //  Process payment
            selectedHotel.rooms[roomChoice - 1].isAvailable = false;
            cout << "\n=====================================================\n";
            cout << "  Payment of Rs. " << selectedHotel.rooms[roomChoice - 1].price
                 << " received via " << paymentMethod << ".\n";
            cout << "  Room booked successfully at " << selectedHotel.name << "!\n";
            cout << "=====================================================\n";

            // Save comprehensive booking details to file
            string bookingDetails = "Booking Confirmation\n" +
                                    string("==============================\n") +
                                    "Tourist Place: " + selectedPlace.name + "\n" +
                                    "Hotel: " + selectedHotel.name + "\n" +
                                    "Room Type: " + selectedHotel.rooms[roomChoice - 1].roomType + "\n" +
                                    "Price: Rs. " + to_string(selectedHotel.rooms[roomChoice - 1].price) + "\n" +
                                    "Payment Method: " + paymentMethod + "\n" +
                                    string("==============================\n");

            // Write to file
            ofstream outFile("booking_details.txt", ios::app); // Open the file in append mode
            outFile << bookingDetails << endl;
            outFile.close();
        }
        else
        {
            //  Process payment
            cout << "\nInvalid payment method! Booking process aborted.\n";
        }
    }
    else
    {
        //  Process payment
        cout << "\nBooking process aborted. Returning to the main menu...\n";
    }
            }
            else
            {
                cout << "\nExiting to the main menu...\n";
            }
            break;
        }

        default:
        {

            // Invalid choice
            cout << "\nInvalid choice! Please choose a valid option (1, 2, or 3).\n";
            break;
        }
    }
}



// Function to handle main menu option
void handleMainMenuOption(int choice, vector<TouristPlace>& places)
{

    switch (choice)
    {
        case 1:
            handleTouristPlaceSelection(places);
            break;

        case 2:
            searchAccommodation(places);
            break;

        case 3:
            displayHotelsByRating(places);
            break;

        case 4:
            bookRoom(places);
            break;

        case 5:
            cancelBooking(places);
            break;

        case 6:
            viewdetails();
            break;

        case 7:
            collectFeedback();
            break;

       // case 8:
          //  thankyou();
          //     loginUser();


        default:
            cout << "\nInvalid option! \nPlease choose a valid option.\n";
            break;
    }

}



void manageAccommodation()
{
    // Sample Data with More Hotels

    vector<TouristPlace> places = {
        TouristPlace(
            "Hampi",
            "Vijayanagar",
            {
                "Temple visits",
                "Exploring ruins",
                "Coracle Ride on Tungabhadra River",
                "Sunset View from Hemakuta Hill",
                "Boulder climbing",
                "Archaeological Museum Visit"
            },
            {
                Hotel(
                    "Vijaya Residency",
                    2.0,
                    0, // pricePerNight (not used in the code)
                    {
                        Room("Single Room", 2000, true),
                        Room("Double Room", 3500, true),
                        Room("Suite", 6000, false)
                    },
                    "Located near the Hampi Bazaar, with easy access to temples.",
                    "+91-8395225001",
                    3.8 // Rating for Vijaya Residency
                ),
                Hotel(
                    "Hampi Heritage Lodge",
                    1.2,
                    0, // pricePerNight (not used in the code)
                    {
                        Room("Single Room", 2200, true),
                        Room("Double Room", 3800, true),
                        Room("Suite", 6500, false)
                    },
                    "Traditional heritage stay with village vibes.",
                    "+91-8395201011",
                    4.0 // Rating for Hampi Heritage Lodge
                ),
                Hotel(
                    "Royal Hampi Resort",
                    3.5,
                    0, // pricePerNight (not used in the code)
                    {
                        Room("Single Room", 3200, true),
                        Room("Double Room", 5000, true),
                        Room("Suite", 9000, true)
                    },
                    "Luxurious resort with a view of the ruins.",
                    "+91-8395222062",
                    4.5 // Rating for Royal Hampi Resort
                ),
                Hotel(
                    "Coracle Inn",
                    4.0,
                    0, // pricePerNight (not used in the code)
                    {
                        Room("Single Room", 2700, false),
                        Room("Double Room", 4500, true),
                        Room("Suite", 7200, true)
                    },
                    "Great for nature lovers, with a riverside view.",
                    "+91-8395226060",
                    4.2 // Rating for Coracle Inn
                ),
                Hotel(
                    "Hampi Guest House",
                    1.5,
                    0, // pricePerNight (not used in the code)
                    {
                        Room("Single Room", 1800, true),
                        Room("Double Room", 3000, false),
                        Room("Suite", 5000, false)
                    },
                    "Budget-friendly, walking distance from the Virupaksha Temple.",
                    "+91-8395222311",
                    3.6 // Rating for Hampi Guest House
                )
            }
        ),
        TouristPlace(
    "Bhadra Wildlife Sanctuary",
    "Chikmagalur, Karnataka",
    {
        "Safari ride to spot tigers and elephants",
        "Bird watching in the sanctuary",
        "Trekking to the Bhadra River",
        "Visit the Honnemaradu Reservoir",
        "Jungle walks with guides",
        "Camping near the river bank"
    },
    {
        Hotel(
            "Bhadra River Resort",
            3.5,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2500, true),
                Room("Double Room", 4500, true),
                Room("Suite", 8000, false)
            },
            "Located near the river with a serene view and wildlife experience.",
            "+91-8192837456",
            4.6 // Rating for Bhadra River Resort
        ),
        Hotel(
            "Wildlife Haven Lodge",
            3.0,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2200, true),
                Room("Double Room", 4000, true),
                Room("Suite", 7000, false)
            },
            "A lodge near the sanctuary offering wildlife safaris and bird watching.",
            "+91-9441035792",
            4.4 // Rating for Wildlife Haven Lodge
        ),
        Hotel(
            "Jungle View Resort",
            2.7,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2100, true),
                Room("Double Room", 3700, true),
                Room("Suite", 6500, false)
            },
            "A nature-inspired resort located deep within the jungle.",
            "+91-9635742824",
            4.2 // Rating for Jungle View Resort
        ),
        Hotel(
            "Bhadra Guest House",
            1.5,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 1700, true),
                Room("Double Room", 3200, false),
                Room("Suite", 5800, false)
            },
            "Budget guest house located near the sanctuary entrance.",
            "+91-9741356548",
            3.5 // Rating for Bhadra Guest House
        ),
        Hotel(
            "Bhadra Sanctuary Resort",
            4.2,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2900, true),
                Room("Double Room", 4800, true),
                Room("Suite", 8500, true)
            },
            "A luxury resort located within the sanctuary, offering guided safaris.",
            "+91-9443202376",
            4.8 // Rating for Bhadra Sanctuary Resort
        )
    }
),

    TouristPlace(
        "Mysore",
        "Mysuru",
        {
            "Mysore Palace",
            "Chamundeshwari Temple",
            "Brindavan Gardens",
            "St. Philomena's Church",
            "KRS Dam"
        },
        {
            Hotel(
                "Radisson Blu Plaza Hotel",
                2.5,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 8500, false)
                },
                "Luxurious hotel with great amenities and proximity to Mysore Palace.",
                "+91-821-4255555",
                4.3
            ),
            Hotel(
                "Royal Orchid Metropole",
                1.8,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4800, true),
                    Room("Suite", 7500, false)
                },
                "Classic heritage hotel located near the city center.",
                "+91-821-2425600",
                4.1
            ),
            Hotel(
                "Lalitha Mahal Palace Hotel",
                3.0,
                0,
                {
                    Room("Single Room", 2800, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 7000, true)
                },
                "Palatial hotel with a grand experience and vintage vibes.",
                "+91-821-2515151",
                4.5
            )
        }
    ),
    TouristPlace(
    "Agumbe",
    "Western Ghats, Karnataka",
    {
        "Visit the Agumbe Rainforest Research Station",
        "Trek to Sunset Point",
        "Explore the Barkana Waterfalls",
        "Nature walk in the rainforests",
        "Spot the famous King Cobra",
        "Photography at the Agumbe village"
    },
    {
        Hotel(
            "Agumbe Rainforest Resort",
            3.0,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2500, true),
                Room("Double Room", 4500, true),
                Room("Suite", 8000, false)
            },
            "A beautiful rainforest resort with a serene view.",
            "+91-9742886766",
            4.3 // Rating for Agumbe Rainforest Resort
        ),
        Hotel(
            "Monsoon Bliss Resort",
            4.0,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 3000, true),
                Room("Double Room", 5000, true),
                Room("Suite", 9000, true)
            },
            "A luxury resort with views of the dense forest and misty hills.",
            "+91-9745922334",
            4.7 // Rating for Monsoon Bliss Resort
        ),
        Hotel(
            "Gokanra Retreat",
            3.5,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2200, true),
                Room("Double Room", 4000, true),
                Room("Suite", 7500, false)
            },
            "A peaceful retreat located near the Gokanra forest.",
            "+91-9483487624",
            4.1 // Rating for Gokanra Retreat
        ),
        Hotel(
            "Agumbe Guest House",
            2.0,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 1800, true),
                Room("Double Room", 3500, false),
                Room("Suite", 6000, false)
            },
            "A budget-friendly option located near the village.",
            "+91-9976234581",
            3.6 // Rating for Agumbe Guest House
        )
    }
),
TouristPlace(
    "Gokarna",
    "Coastal Karnataka",
    {
        "Visit the Om Beach",
        "Relax at Kudle Beach",
        "Explore the Mirjan Fort",
        "Visit the Gokarna Temple",
        "Trekking along the beaches",
        "Camp under the stars at Half Moon Beach"
    },
    {
        Hotel(
            "Om Beach Resort",
            4.2,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2800, true),
                Room("Double Room", 4500, true),
                Room("Suite", 8500, false)
            },
            "Located on Om Beach with a perfect view of the sunset.",
            "+91-9449320105",
            4.5 // Rating for Om Beach Resort
        ),
        Hotel(
            "Kudle Beach View Resort",
            3.5,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 2500, true),
                Room("Double Room", 4200, true),
                Room("Suite", 7500, false)
            },
            "A peaceful resort with views of the beautiful Kudle Beach.",
            "+91-9448267342",
            4.3 // Rating for Kudle Beach View Resort
        ),
        Hotel(
            "Namaste Cafe and Beach Resort",
            2.8,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 1800, true),
                Room("Double Room", 3200, true),
                Room("Suite", 6000, false)
            },
            "A beachfront cafe and resort offering an amazing stay experience.",
            "+91-8383007607",
            3.9 // Rating for Namaste Cafe and Beach Resort
        ),
        Hotel(
            "Gokarna International Beach Resort",
            3.8,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 3500, true),
                Room("Double Room", 5500, true),
                Room("Suite", 9500, true)
            },
            "Luxurious beach resort offering stunning views and top-notch amenities.",
            "+91-9343832087",
            4.6 // Rating for Gokarna International Beach Resort
        ),
        Hotel(
            "Gokarna Guest House",
            1.5,
            0, // pricePerNight (not used in the code)
            {
                Room("Single Room", 1200, true),
                Room("Double Room", 2500, false),
                Room("Suite", 4500, false)
            },
            "Budget-friendly guest house, walking distance from the beach.",
            "+91-9612345780",
            3.4 // Rating for Gokarna Guest House
        )
    }
),
    TouristPlace(
        "Bangalore",
        "Bangalore Urban",
        {
            "Bangalore Palace",
            "Lalbagh Botanical Garden",
            "Vidhana Soudha",
            "Nandi Hills",
            "ISKCON Temple",
            "Cubbon Park",
            "Bannerghatta Biological Park"
        },
        {
            Hotel(
                "Taj West End",
                3.0,
                0,
                {
                    Room("Single Room", 7000, true),
                    Room("Double Room", 9500, true),
                    Room("Suite", 15000, false)
                },
                "Luxury hotel offering a peaceful getaway in the heart of Bangalore.",
                "+91-80-66605656",
                4.7
            ),
            Hotel(
                "The Leela Palace",
                4.0,
                0,
                {
                    Room("Single Room", 8000, true),
                    Room("Double Room", 11000, true),
                    Room("Suite", 18000, false)
                },
                "One of Bangalore's finest, known for its impeccable service and elegant design.",
                "+91-80-25211234",
                4.8
            ),
            Hotel(
                "Sheraton Grand Bangalore Hotel",
                2.5,
                0,
                {
                    Room("Single Room", 5500, true),
                    Room("Double Room", 7800, true),
                    Room("Suite", 13000, true)
                },
                "A modern hotel with great facilities and a central location.",
                "+91-80-42521000",
                4.3
            )
        }
    ),
    TouristPlace(
        "Coorg",
        "Kodagu",
        {
            "Abbey Falls",
            "Raja's Seat",
            "Dubare Elephant Camp",
            "Namdroling Monastery",
            "Coffee Plantations"
        },
        {
            Hotel(
                "The Tamara Coorg",
                5.0,
                0,
                {
                    Room("Single Room", 11000, true),
                    Room("Double Room", 15000, true),
                    Room("Suite", 25000, true)
                },
                "Luxury resort surrounded by nature, offering great views of the coffee plantations.",
                "+91-8272-281999",
                4.7
            ),
            Hotel(
                "Eagle Ridge Resort",
                3.0,
                0,
                {
                    Room("Single Room", 4500, true),
                    Room("Double Room", 7500, true),
                    Room("Suite", 12000, false)
                },
                "Nestled in the hills, perfect for a peaceful retreat.",
                "+91-8272-276600",
                4.1
            ),
            Hotel(
                "Coorg Wilderness Resort",
                4.5,
                0,
                {
                    Room("Single Room", 9000, true),
                    Room("Double Room", 13000, true),
                    Room("Suite", 20000, true)
                },
                "Exclusive eco-friendly resort with a private atmosphere.",
                "+91-8272-225555",
                4.6
            )
        }
    ),
    TouristPlace(
        "Chikmagalur",
        "Chikmagalur",
        {
            "Mullayanagiri",
            "Baba Budangiri",
            "Hebbe Falls",
            "Coffee Plantations",
            "Kudremukh National Park"
        },
        {
            Hotel(
                "The Serai Chikmagalur",
                4.5,
                0,
                {
                    Room("Single Room", 9500, true),
                    Room("Double Room", 13500, true),
                    Room("Suite", 20000, true)
                },
                "A serene resort offering an unforgettable experience amid lush green landscapes.",
                "+91-8262-226000",
                4.6
            ),
            Hotel(
                "Gateway Chikmagalur",
                3.0,
                0,
                {
                    Room("Single Room", 5500, true),
                    Room("Double Room", 8000, true),
                    Room("Suite", 13000, false)
                },
                "Peaceful hotel with great views and a cozy ambiance.",
                "+91-8262-232040",
                4.2
            ),
            Hotel(
                "Java Rain Resorts",
                3.5,
                0,
                {
                    Room("Single Room", 8000, true),
                    Room("Double Room", 12000, true),
                    Room("Suite", 18000, true)
                },
                "Exclusive resort offering a luxurious experience with breathtaking views.",
                "+91-8262-260000",
                4.7
            )
        }
    ),
    TouristPlace(
        "Udupi",
        "Udupi",
        {
            "Sri Krishna Temple",
            "St. Mary's Island",
            "Malpe Beach",
            "Udupi Manipal"
        },
        {
            Hotel(
                "Hotel Udupi Residency",
                2.5,
                0,
                {
                    Room("Single Room", 2000, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Budget-friendly hotel near the Sri Krishna Temple.",
                "+91-820-2551077",
                3.9
            ),
            Hotel(
                "Paradise Isle Beach Resort",
                1.8,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5500, true),
                    Room("Suite", 8000, true)
                },
                "Beachfront resort with a relaxing atmosphere and excellent facilities.",
                "+91-820-2585302",
                4.4
            ),
            Hotel(
                "The Ocean Pearl",
                2.0,
                0,
                {
                    Room("Single Room", 2700, true),
                    Room("Double Room", 4300, true),
                    Room("Suite", 6500, false)
                },
                "Comfortable stay with a close proximity to the beach.",
                "+91-820-2222222",
                4.3
            )
        }
    ),
    TouristPlace(
        "Hassan",
        "Hassan",
        {
            "Hoysaleswara Temple",
            "Chennakesava Temple",
            "Shravanabelagola (Bahubali Statue)"
        },
        {
            Hotel(
                "Hoysala Village Resort",
                3.5,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 7000, false)
                },
                "A heritage-style resort offering a peaceful stay amidst nature.",
                "+91-8177-256800",
                4.4
            ),
            Hotel(
                "Hotel S K Regency",
                1.8,
                0,
                {
                    Room("Single Room", 2200, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5500, false)
                },
                "Budget-friendly hotel with easy access to the city s attractions.",
                "+91-8177-227100",
                3.9
            ),
            Hotel(
                "KSRTC Guest House",
                2.0,
                0,
                {
                    Room("Single Room", 1800, true),
                    Room("Double Room", 2800, true),
                    Room("Suite", 4500, false)
                },
                "Basic guest house for budget travelers.",
                "+91-8177-226200",
                3.5
            )
        }
    ),
    TouristPlace(
        "Kabini",
        "Kodagu",
        {
            "Kabini River",
            "Kabini Wildlife Sanctuary",
            "Jungle Safaris"
        },
        {
            Hotel(
                "The Serai Kabini",
                4.5,
                0,
                {
                    Room("Single Room", 12000, true),
                    Room("Double Room", 18000, true),
                    Room("Suite", 25000, true)
                },
                "Luxury resort offering safaris and pristine views of the Kabini River.",
                "+91-8272-273000",
                4.7
            ),
            Hotel(
                "Orange County Kabini",
                4.0,
                0,
                {
                    Room("Single Room", 15000, true),
                    Room("Double Room", 22000, true),
                    Room("Suite", 30000, false)
                },
                "Exclusive resort with nature trails and beautiful riverside views.",
                "+91-8272-236000",
                4.6
            ),
            Hotel(
                "Kabini River Lodge",
                3.8,
                0,
                {
                    Room("Single Room", 8000, true),
                    Room("Double Room", 12000, true),
                    Room("Suite", 20000, true)
                },
                "Government-run lodge with rustic charm and safari options.",
                "+91-8272-271350",
                4.2
            )
        }
    ),
    TouristPlace(
        "Badami",
        "Bagalkot",
        {
            "Badami Caves",
            "Agastya Lake",
            "Bhuthnatha Temple",
            "Fort",
            "Palace"
        },
        {
            Hotel(
                "KSTDC Hotel Mayura Chalukya",
                2.5,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 6000, false)
                },
                "Simple government-run hotel with close access to the Badami Caves.",
                "+91-8382-220500",
                3.8
            ),
            Hotel(
                "Badami Court Hotel",
                3.0,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 7000, false)
                },
                "Comfortable hotel offering modern amenities and proximity to key attractions.",
                "+91-8382-220233",
                4.2
            ),
            Hotel(
                "Hotel Mayura",
                2.0,
                0,
                {
                    Room("Single Room", 1800, true),
                    Room("Double Room", 2800, true),
                    Room("Suite", 4200, false)
                },
                "Basic stay option, suitable for budget travelers.",
                "+91-8382-220366",
                3.5
            )
        }
    ),
    TouristPlace(
        "Bijapur",
        "Vijayapura",
        {
            "Gol Gumbaz",
            "Bijapur Fort",
            "Ibrahim Rauza",
            "Jami Masjid"
        },
        {
            Hotel(
                "Hotel Basava Residency",
                2.5,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 3800, true),
                    Room("Suite", 5500, false)
                },
                "Affordable hotel with access to local landmarks.",
                "+91-8382-263344",
                3.7
            ),
            Hotel(
                "KSTDC Hotel Mayura",
                1.8,
                0,
                {
                    Room("Single Room", 2200, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Basic government-run hotel with clean rooms.",
                "+91-8382-262800",
                3.6
            ),
            Hotel(
                "Kishkinda Heritage Resort",
                3.2,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 6500, false)
                },
                "Heritage-style resort near Bijapur Fort, perfect for history lovers.",
                "+91-8382-261208",
                4.0
            )
        }
    ),
    TouristPlace(
        "Dandeli",
        "Uttara Kannada",
        {
            "Dandeli Wildlife Sanctuary",
            "Kali River",
            "Syntheri Rocks",
            "Anshi National Park"
        },
        {
            Hotel(
                "Dandeli Jungle Resort",
                3.5,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 7500, true)
                },
                "Eco-friendly resort located near Dandeli Wildlife Sanctuary with various activities.",
                "+91-8382-264409",
                4.5
            ),
            Hotel(
                "The River View Resort",
                3.0,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 6500, false)
                },
                "Secluded riverside resort offering serene views and adventure activities.",
                "+91-8382-223344",
                4.1
            ),
            Hotel(
                "Wilderness Resort",
                2.8,
                0,
                {
                    Room("Single Room", 2800, true),
                    Room("Double Room", 4200, true),
                    Room("Suite", 6000, false)
                },
                "Basic resort with options for jungle safaris and nature walks.",
                "+91-8382-228888",
                4.0
            )
        }
    ),
    TouristPlace(
        "Sakleshpur",
        "Hassan",
        {
            "Manjarabad Fort",
            "Bisle Reserve Forest",
            "Coffee Plantations",
            "Sakleshpur Hills"
        },
        {
            Hotel(
                "The Coffee Bean Resort",
                4.0,
                0,
                {
                    Room("Single Room", 7000, true),
                    Room("Double Room", 10000, true),
                    Room("Suite", 15000, true)
                },
                "A cozy resort set amidst coffee plantations and serene hills.",
                "+91-8197-203400",
                4.5
            ),
            Hotel(
                "The Windflower Resort & Spa",
                4.5,
                0,
                {
                    Room("Single Room", 9000, true),
                    Room("Double Room", 13000, true),
                    Room("Suite", 18000, true)
                },
                "Exclusive resort with beautiful views, wellness facilities, and modern amenities.",
                "+91-820-2571100",
                4.6
            ),
            Hotel(
                "Hoysala Village Resort",
                3.0,
                0,
                {
                    Room("Single Room", 4000, true),
                    Room("Double Room", 6000, true),
                    Room("Suite", 9000, false)
                },
                "Classic resort offering traditional ambiance and a relaxing environment.",
                "+91-820-2506099",
                4.2
            )
        }
    ),
    TouristPlace(
        "Tungabhadra Dam",
        "Hospet, Ballari",
        {
            "Tungabhadra Dam",
            "Anjaneya Hill",
            "Hampi"
        },
        {
            Hotel(
                "Vijaya Residency",
                2.0,
                0,
                {
                    Room("Single Room", 2000, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 6000, false)
                },
                "Located near the Hampi Bazaar, with easy access to temples.",
                "+91-8395225001",
                3.8
            ),
            Hotel(
                "Hampi Heritage Lodge",
                1.2,
                0,
                {
                    Room("Single Room", 2200, true),
                    Room("Double Room", 3800, true),
                    Room("Suite", 6500, false)
                },
                "Traditional heritage stay with village vibes.",
                "+91-8395201011",
                4.0
            ),
            Hotel(
                "Royal Hampi Resort",
                3.5,
                0,
                {
                    Room("Single Room", 3200, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 9000, true)
                },
                "Luxurious resort with a view of the ruins.",
                "+91-8395222062",
                4.5
            )
        }
    ),
    TouristPlace(
        "Ranganathittu Bird Sanctuary",
        "Mandya",
        {
            "Bird Watching",
            "Crocodile Observation",
            "Nature Walks"
        },
        {
            Hotel(
                "KSTDC Mayura Ranganathittu",
                2.0,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 5500, false)
                },
                "Affordable stay with proximity to the bird sanctuary.",
                "+91-8272-256200",
                3.8
            ),
            Hotel(
                "Hotel Kadamba",
                2.5,
                0,
                {
                    Room("Single Room", 2000, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Budget hotel ideal for short stays with basic facilities.",
                "+91-8272-240500",
                3.6
            ),
            Hotel(
                "Srirangapatna Resort",
                3.2,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 7000, true)
                },
                "Eco-resort with river views and bird watching activities.",
                "+91-8272-243400",
                4.0
            )
        }
    ),
    TouristPlace(
        "Channarayana Durga",
        "Tumkur",
        {
            "Hill Trekking",
            "Channarayana Durga Fort"
        },
        {
            Hotel(
                "Hotel Sai Prakash",
                2.0,
                0,
                {
                    Room("Single Room", 2200, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Simple and affordable hotel located in Tumkur.",
                "+91-8162-251433",
                3.7
            ),
            Hotel(
                "Channarayana Durga Resort",
                3.5,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 6500, false)
                },
                "Resort offering a peaceful stay with views of the Channarayana Durga hills.",
                "+91-8162-239800",
                4.0
            ),
            Hotel(
                "Tumkur Viceroy",
                2.5,
                0,
                {
                    Room("Single Room", 1800, true),
                    Room("Double Room", 2800, true),
                    Room("Suite", 4200, false)
                },
                "Budget hotel with basic amenities.",
                "+91-8162-252221",
                3.5
            )
        }
    ),
    TouristPlace(
        "Shravanabelagola",
        "Hassan",
        {
            "Gommateshwara (Bahubali Statue)",
            "Shravanabelagola Hill",
            "Jain Temples"
        },
        {
            Hotel(
                "Shravanabelagola Resort",
                3.0,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 6000, false)
                },
                "Simple stay near the famous Bahubali statue.",
                "+91-8177-258300",
                3.9
            ),
            Hotel(
                "Hotel Mayura",
                2.5,
                0,
                {
                    Room("Single Room", 2000, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Basic and budget-friendly stay option.",
                "+91-8177-258500",
                3.6
            ),
            Hotel(
                "Jain Heritage Stay",
                3.2,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 7000, false)
                },
                "A serene and quiet stay with a heritage touch.",
                "+91-8177-259000",
                4.1
            )
        }
    ),
    TouristPlace(
        "Mangaluru",
        "Dakshina Kannada",
        {
            "Panambur Beach",
            "Tannirbhavi Beach",
            "St. Aloysius Chapel",
            "Kudroli Gokarnath Temple"
        },
        {
            Hotel(
                "The Gateway Hotel",
                3.5,
                0,
                {
                    Room("Single Room", 4000, true),
                    Room("Double Room", 6000, true),
                    Room("Suite", 8000, true)
                },
                "A luxury hotel with modern amenities and excellent service.",
                "+91-824-2222200",
                4.3
            ),
            Hotel(
                "Hotel Moti Mahal",
                2.0,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 5500, false)
                },
                "Affordable hotel with a convenient location in Mangaluru.",
                "+91-824-2225600",
                3.8
            ),
            Hotel(
                "Ocean Pearl",
                2.8,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 7000, false)
                },
                "Beachside hotel with a relaxing atmosphere and top-notch services.",
                "+91-824-6667777",
                4.1
            )
        }
    ),
    TouristPlace(
        "Kudremukh",
        "Chikmagalur",
        {
            "Kudremukh National Park",
            "Kudremukh Peak",
            "Trekking"
        },
        {
            Hotel(
                "Kudremukh Wildlife Resort",
                3.5,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 7000, true)
                },
                "A tranquil resort offering trekking and nature walks.",
                "+91-8262-277555",
                4.5
            ),
            Hotel(
                "Trekking Trails Resort",
                3.0,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 6000, false)
                },
                "Budget-friendly stay with trekking options to explore the natural beauty.",
                "+91-8262-273300",
                4.0
            ),
            Hotel(
                "Chikmagalur Coffee Estate Resort",
                4.2,
                0,
                {
                    Room("Single Room", 5000, true),
                    Room("Double Room", 7000, true),
                    Room("Suite", 9000, true)
                },
                "A resort located within coffee plantations offering serene views and hiking trails.",
                "+91-8262-290000",
                4.6
            )
        }
    ),
    TouristPlace(
        "Kalburgi",
        "Kalaburagi",
        {
            "Gulbarga Fort",
            "Jama Masjid",
            "Sharana Basaveshwara Temple"
        },
        {
            Hotel(
                "Hotel KSTDC Mayura",
                2.5,
                0,
                {
                    Room("Single Room", 2000, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Located near the Gulbarga Fort, this hotel offers basic amenities.",
                "+91-8482-240800",
                3.6
            ),
            Hotel(
                "Hotel Ashoka",
                3.0,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 5500, false)
                },
                "Budget-friendly stay with simple comforts, located centrally in Kalaburagi.",
                "+91-8482-256990",
                3.7
            ),
            Hotel(
                "Siri Hotel",
                2.8,
                0,
                {
                    Room("Single Room", 2200, true),
                    Room("Double Room", 3800, true),
                    Room("Suite", 6000, false)
                },
                "Ideal for short stays with comfortable rooms and basic services.",
                "+91-8482-258000",
                3.5
            )
        }
    ),
    TouristPlace(
        "Yellapur",
        "Uttara Kannada",
        {
            "Magod Falls",
            "Sathodi Falls",
            "Unchalli Falls",
            "Suwarna River"
        },
        {
            Hotel(
                "Sathodi Resort",
                3.2,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 6000, false)
                },
                "Peaceful resort surrounded by waterfalls and lush greenery.",
                "+91-8392-279200",
                4.0
            ),
            Hotel(
                "Unchalli Falls Eco Retreat",
                3.8,
                0,
                {
                    Room("Single Room", 3000, true),
                    Room("Double Room", 4500, true),
                    Room("Suite", 7000, false)
                },
                "Eco-friendly retreat with river views and trekking opportunities.",
                "+91-8392-280500",
                4.2
            ),
            Hotel(
                "Yellapur Jungle Lodge",
                4.0,
                0,
                {
                    Room("Single Room", 2200, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5500, false)
                },
                "Jungle lodge offering an adventurous stay with wildlife experiences.",
                "+91-8392-285600",
                4.1
            )
        }
    ),
    TouristPlace(
        "Chamundi Hill",
        "Mysuru",
        {
            "Chamundeshwari Temple",
            "Chamundi Hill Viewpoint",
            "Nandi Statue"
        },
        {
            Hotel(
                "Hotel Royal Orchid",
                3.5,
                0,
                {
                    Room("Single Room", 4000, true),
                    Room("Double Room", 6000, true),
                    Room("Suite", 8000, true)
                },
                "A luxury hotel with breathtaking views of the Chamundi Hill.",
                "+91-821-2423030",
                4.2
            ),
            Hotel(
                "Hotel Southern Star",
                2.8,
                0,
                {
                    Room("Single Room", 2500, true),
                    Room("Double Room", 4000, true),
                    Room("Suite", 5500, false)
                },
                "Comfortable mid-range hotel offering convenient access to the Chamundi Hill temple.",
                "+91-821-2425225",
                3.9
            ),
            Hotel(
                "KSTDC Mayura",
                2.0,
                0,
                {
                    Room("Single Room", 2000, true),
                    Room("Double Room", 3500, true),
                    Room("Suite", 5000, false)
                },
                "Budget-friendly hotel with basic amenities and a good location.",
                "+91-821-2412300",
                3.5
            ),
            Hotel(
                "Ramada by Wyndham",
                3.0,
                0,
                {
                    Room("Single Room", 3500, true),
                    Room("Double Room", 5000, true),
                    Room("Suite", 7000, false)
                },
                "Upscale hotel with excellent amenities, located near Chamundi Hill.",
                "+91-821-2446000",
                4.3
            )
        }
    )
};

 // Display Welcome Message
   // displayWelcomeMessage();

    // Main Menu Loop
    while (true) {
        displayMenu();
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 8)
        {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number (1-7): ";
        }

        handleMainMenuOption(choice, places);

        if (choice == 8)
        break;
    }
}





class TrainRoute {
public:
    TrainRoute(const string& name, const string& source, const string& destination, int distance)
        : name(name), source(source), destination(destination), distance(distance) {}

    string getName() const { return name; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    int getDistance() const { return distance; }

private:
    string name;
    string source;
    string destination;
    int distance;
};



class Train {
public:
    Train(const string& trainNumber, const TrainRoute& route, int totalSeats, const string& trainTiming, double fare)
        : trainNumber(trainNumber), route(route), totalSeats(totalSeats), trainTiming(trainTiming), fare(fare) {
        seats.resize(totalSeats, false);
    }

    bool reserveSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats && !seats[seatNumber - 1]) {
            seats[seatNumber - 1] = true;
            return true;
        }
        return false;
    }

    bool cancelSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats && seats[seatNumber - 1]) {
            seats[seatNumber - 1] = false;
            return true;
        }
        return false;
    }

    void displayTrainInfo() const {
        cout << "\n\t\t\tTrain Number: " << trainNumber << endl;
        cout << "\t\tRoute: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
        cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        cout << "\t\t\tTotal Seats: " << totalSeats << endl;
        cout << "\t\t\tTrain Timing: " << trainTiming << endl;
        cout << "\t\t\tFare: ₹" << fare << endl;
        cout << "\t\t----- Available Seats -----\n";
        bool flag = false;
        for (int i = 0; i < totalSeats; i++) {
            if (!seats[i]) {
                cout << "\t\t" << i + 1;
            } else {
                cout << "\t\tNA";
            }
            if (!flag) {
                cout << "\t";
                flag = true;
            } else {
                cout << "\n";
                flag = false;
            }
        }
        cout << endl;
    }

    void displayAvailableSeats() const {
        cout << "\t\t\tAvailable Seats on Train " << trainNumber << ":\n";
        for (int i = 0; i < totalSeats; ++i) {
            if (!seats[i]) {
                cout << "\t\t\tSeat " << i + 1 << ": Available\n";
            }
        }
    }

    void displayTrainStatus() const {
        int reservedSeats = 0;
        for (int i = 0; i < totalSeats; ++i) {
            if (seats[i]) {
                reservedSeats++;
            }
        }

        cout << "Train Status for Train " << trainNumber << ":\n";
        cout << "Total Seats: " << totalSeats << "\n";
        cout << "Reserved Seats: " << reservedSeats << "\n";
        cout << "Available Seats: " << totalSeats - reservedSeats << "\n";
    }

    string getTrainNumber() const { return trainNumber; }
    const TrainRoute& getRoute() const { return route; }
    int getTotalSeats() const { return totalSeats; }
    string getTrainTiming() const { return trainTiming; }
    double getFare() const { return fare; }

private:
    string trainNumber;
    TrainRoute route;
    int totalSeats;
    string trainTiming;
    double fare;
    vector<bool> seats;
};

class TrainTicket {
public:
    TrainTicket(const string& passengerName, int seatNumber, TrainRoute& route, const Train& train)
        : passengerName(passengerName), seatNumber(seatNumber), route(route), train(train) {}

    string getPassengerName() const { return passengerName; }
    int getSeatNumber() const { return seatNumber; }
    const TrainRoute& getRoute() const { return route; }
    const Train& getTrain() const { return train; }

private:
    string passengerName;
    int seatNumber;
    TrainRoute route;
    Train train;
};

class TrainUser {
public:
    TrainUser(const string& username, const string& password)
        : username(username), password(password) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    void addTicket(TrainTicket& newTicket) { tickets.push_back(newTicket); }
    void removeTicket(int index) { tickets.erase(tickets.begin() + index - 1); }
    void printAllTickets() const {
        for (size_t i = 0; i < tickets.size(); ++i) {
            cout << "\n\t\t------ Ticket " << i + 1 << " ------" << endl;
            cout << "\t\t\tPassenger: " << tickets[i].getPassengerName() << endl;
            cout << "\t\t\tRoute: " << tickets[i].getRoute().getName() << " (" << tickets[i].getRoute().getSource() << " to " << tickets[i].getRoute().getDestination() << ")\n";
            cout << "\t\t\tTrain Number: " << tickets[i].getTrain().getTrainNumber() << endl;
            cout << "\t\t\tSeat Number: " << tickets[i].getSeatNumber() << endl;
        }
    }

    int numberOfTickets() const { return tickets.size(); }
    TrainTicket& getTicket(int index) { return tickets[index - 1]; }

private:
    string username;
    string password;
    vector<TrainTicket> tickets;
};

// Define the TrainReservationSystem class with necessary member functions
class TrainReservationSystem {
public:
    TrainReservationSystem() {
        // Load routes from file
        ifstream routesFile("train_routes.txt");
        if (routesFile.is_open()) {
            string line;
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string name, source, destination;
                int distance;
                getline(ss, name, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;
                routes.push_back(TrainRoute(name, source, destination, distance));
            }
            routesFile.close();
        }

        // Load trains from file
ifstream trainsFile("trains.txt");
if (trainsFile.is_open()) {
    string line;
    while (getline(trainsFile, line)) {
        stringstream ss(line);
        string trainNumber, routeName, trainTiming;
        int totalSeats;
        double fare;

        getline(ss, trainNumber, ',');
        getline(ss, routeName, ',');
        ss >> totalSeats;
        ss.ignore(); // Ignore the comma
        getline(ss, trainTiming, ',');
        ss >> fare;

        for (const TrainRoute& route : routes) {
            if (route.getName() == routeName) {
                trains.push_back(Train(trainNumber, route, totalSeats, trainTiming, fare));
                break;
            }
        }
    }
    trainsFile.close();
}
    }

    void registerUser(const string& username, const string& password) {
        users.push_back(TrainUser(username, password));
        cout << "\n\t\tUser registered successfully. Please login to continue!\n";
    }

    bool authenticateUser(const string& username, const string& password) {
        for (const TrainUser& user : users) {
            string lowercaseUsername = user.getUsername();
            string lowercaseInputUsername = username;
            transform(lowercaseUsername.begin(), lowercaseUsername.end(), lowercaseUsername.begin(), ::tolower);
            transform(lowercaseInputUsername.begin(), lowercaseInputUsername.end(), lowercaseInputUsername.begin(), ::tolower);

            if (lowercaseUsername == lowercaseInputUsername && user.getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    string getPassword() {
        string password;
        char ch;
        while (true) {
            ch = _getch(); 
            if (ch == '\r') { 
                cout << endl;
                break;
            } else if (ch == '\b' && !password.empty()) { 
                password.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                password += ch;
                cout << '*'; 
            }
        }
        return password;
    }


void changeUserPassword(const string& username) {
    string filename = "train_user_credentials.txt";
    ifstream file(filename);
    bool userFound = false;
    vector<string> lines;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                if (storedUsername == username) {
                    userFound = true;
                    cout << "\n\t\tEnter new password for user '" << username << "': ";
                    string newPassword = getPassword();

                    // Replace the password in the line
                    line = username + "," + newPassword;
                }
            }
            lines.push_back(line); // Keep all lines in memory
        }
        file.close();
    } else {
        cout << "\n\t\tError: Unable to open file for reading.\n";
        return;
    }

    if (userFound) {
        ofstream outFile(filename, ios::trunc); // Overwrite the file
        if (outFile.is_open()) {
            for (const string& updatedLine : lines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();
            cout << "\n\t\tPassword updated successfully!\n";
        } else {
            cout << "\n\t\tError: Unable to open file for updating.\n";
        }
    } else {
        cout << "\n\t\tError: Username '" << username << "' not found in the system.\n";
    }
}

void changeTrainAdminPassword(const string& username) {
    string filename = "train_admin_credentials.txt";
    ifstream file(filename);
    bool userFound = false;
    vector<string> lines;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                if (storedUsername == username) {
                    userFound = true;
                    cout << "\n\t\tEnter new password for train admin '" << username << "': ";
                    string newPassword = getPassword();

                    // Replace the password in the line
                    line = username + "," + newPassword;
                }
            }
            lines.push_back(line); // Keep all lines in memory
        }
        file.close();
    } else {
        cout << "\n\t\tError: Unable to open file for reading.\n";
        return;
    }

    if (userFound) {
        ofstream outFile(filename, ios::trunc); // Overwrite the file
        if (outFile.is_open()) {
            for (const string& updatedLine : lines) {
                outFile << updatedLine << "\n";
            }
            outFile.close();
            cout << "\n\t\tPassword updated successfully!\n";
        } else {
            cout << "\n\t\tError: Unable to open file for updating.\n";
        }
    } else {
        cout << "\n\t\tError: Username '" << username << "' not found in the system.\n";
    }
}




    TrainUser& findUser(const string& username) {
        for (TrainUser& user : users) {
            if (user.getUsername() == username) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }

    void displayRoutes() const {
        cout << "\n\t\t------ Available Train Routes ------\n";
        for (const TrainRoute& route : routes) {
            cout << "\n\t\tRoute Name: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
            cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        }
    }

    void displayTrains() const {
        cout << "\t\t------ Available Trains ------\n";
        for (const Train& train : trains) {
            train.displayTrainInfo();
            cout << endl;
        }
    }

    void displayTrainsForRoute(int selectedRoute) const {
        cout << "\t\t\tTrains available for Route " << routes[selectedRoute - 1].getName() << ":\n";
        for (const Train& train : trains) {
            if (train.getRoute().getName() == routes[selectedRoute - 1].getName()) {
                train.displayTrainInfo();
                cout << endl;
            }
        }
    }

    
   void bookTrainTicket(const string& username) {
    string source, destination;
    int numberOfTickets;

    set<string> locations; // Set to store unique locations
    for (const auto& route : routes) {
        string source = route.getSource();
        source.erase(0, source.find_first_not_of(" \t")); // Trim leading spaces
        source.erase(source.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(source);

        string destination = route.getDestination();
        destination.erase(0, destination.find_first_not_of(" \t")); // Trim leading spaces
        destination.erase(destination.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(destination);
    }

    cout << "\n\tAvailable Locations:\n";
    for (const string& location : locations) {
        cout << "\t- " << location << "\n";
    }

    cout << "\n\tEnter Source: ";
    cin.ignore();
    getline(cin, source);
    cout << "\tEnter Destination: ";
    getline(cin, destination);

    vector<int> matchingRoutes;
    cout << "\n\tAvailable Routes:\n";
    for (size_t i = 0; i < routes.size(); ++i) {
        if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
            cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
            matchingRoutes.push_back(i);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "\n\tNo routes available for the entered source and destination.\n";
        return;
    }

    string selectedRouteName;
    cout << "\n\tSelect a Route (Enter the Route Name): ";
    getline(cin, selectedRouteName);

    int selectedRoute = -1;
    for (size_t i = 0; i < matchingRoutes.size(); ++i) {
        if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
            selectedRoute = matchingRoutes[i];
            break;
        }
    }

    if (selectedRoute == -1) {
        cout << "\n\tInvalid route name. Please try again.\n";
        return;
    }

    vector<int> matchingTrains;
    cout << "\n\tAvailable Trains for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].getRoute().getName() == routes[selectedRoute].getName()) {
            cout << "\t" << i + 1 << ". Train Number: " << trains[i].getTrainNumber() << "\n";
            matchingTrains.push_back(i);
        }
    }

    if (matchingTrains.empty()) {
        cout << "\n\tNo trains available for the selected route.\n";
        return;
    }

    int selectedTrainNumber;
    cout << "\n\tSelect a Train (Enter the Train Number): ";
    cin >> selectedTrainNumber;

    string selectedTrainString = to_string(selectedTrainNumber);

    int selectedTrainIndex = -1;
    for (size_t i = 0; i < matchingTrains.size(); ++i) {
        if (trains[matchingTrains[i]].getTrainNumber() == selectedTrainString) {
            selectedTrainIndex = matchingTrains[i];
            break;
        }
    }

    if (selectedTrainIndex == -1) {
        cout << "\n\tInvalid train number. Please try again.\n";
        return;
    }

    trains[selectedTrainIndex].displayAvailableSeats();

    cout << "\n\tEnter the number of tickets you want to book: ";
    cin >> numberOfTickets;

    if (cin.fail() || numberOfTickets < 1 || numberOfTickets > trains[selectedTrainIndex].getTotalSeats()) {
        cout << "\n\tInvalid number of tickets. Please try again.\n";
        return;
    }

    vector<pair<string, int>> travelers;

    for (int i = 1; i <= numberOfTickets; ++i) {
        string travelerName;
        int travelerAge;
        cout << "\n\tEnter Traveler " << i << "'s Name: ";
        cin.ignore();
        getline(cin, travelerName);
        cout << "\tEnter Traveler " << i << "'s Age: ";
        cin >> travelerAge;

        travelers.push_back({travelerName, travelerAge});
    }

    vector<TrainTicket> userTickets;
    for (int i = 0; i < numberOfTickets; ++i) {
        int selectedSeat;
        cout << "\n\tEnter Seat Number for Traveler " << (i + 1) << ": ";
        cin >> selectedSeat;

        if (cin.fail() || selectedSeat < 1 || selectedSeat > trains[selectedTrainIndex].getTotalSeats() || !trains[selectedTrainIndex].reserveSeat(selectedSeat)) {
            cout << "\n\tInvalid or unavailable seat number. Booking failed for Traveler " << (i + 1) << ".\n";
            continue;
        }

        TrainTicket ticket(travelers[i].first, selectedSeat, routes[selectedRoute], trains[selectedTrainIndex]);
        userTickets.push_back(ticket);

        cout << "\n\t\t\tTicket for Traveler " << (i + 1) << ":\n";
        cout << "\t\t\tPassenger: " << ticket.getPassengerName() << " (Age: " << travelers[i].second << ")\n";
        cout << "\t\t\tTrain Number: " << trains[selectedTrainIndex].getTrainNumber() << "\n";
        cout << "\t\t\tRoute: " << ticket.getRoute().getName() << " (" << ticket.getRoute().getSource() << " to " << ticket.getRoute().getDestination() << ")\n";
        cout << "\t\t\tSeat Number: " << ticket.getSeatNumber() << "\n";
    }

    trains[selectedTrainIndex].displayTrainStatus();

    ofstream ticketsFile("train_tickets.txt", ios::app);
    if (ticketsFile.is_open()) {
        for (const auto& ticket : userTickets) {
            ticketsFile << username << "," << ticket.getPassengerName() << "," << ticket.getSeatNumber() << ","
                        << ticket.getRoute().getName() << "," << ticket.getTrain().getTrainNumber() << "\n";
        }
        ticketsFile.close();
    }

    printUserTickets(username);
}

/*void bookTrainTicket(const string& username) {
    string source, destination;
    int numberOfTickets;
    set<string> locations;

    // Gather all unique locations from routes
    for (const auto& route : routes) {
        string routeSource = route.getSource();
        routeSource.erase(0, routeSource.find_first_not_of(" \t"));
        routeSource.erase(routeSource.find_last_not_of(" \t") + 1);
        locations.insert(routeSource);

        string routeDestination = route.getDestination();
        routeDestination.erase(0, routeDestination.find_first_not_of(" \t"));
        routeDestination.erase(routeDestination.find_last_not_of(" \t") + 1);
        locations.insert(routeDestination);
    }

    // Display available locations
    cout << "\n\tAvailable Locations:\n";
    for (const string& location : locations) {
        cout << "\t- " << location << "\n";
    }

    // Prompt user for source and destination
    cout << "\n\tEnter Source: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear previous input
    getline(cin, source);
    cout << "\tEnter Destination: ";
    getline(cin, destination);

    // Find matching routes
    vector<int> matchingRoutes;
    cout << "\n\tAvailable Routes:\n";
    for (size_t i = 0; i < routes.size(); ++i) {
        if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
            cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
            matchingRoutes.push_back(i);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "\n\tNo routes available for the entered source and destination.\n";
        return;
    }

    // Select a route
    string selectedRouteName;
    cout << "\n\tSelect a Route (Enter the Route Name): ";
    getline(cin, selectedRouteName);

    int selectedRoute = -1;
    for (size_t i = 0; i < matchingRoutes.size(); ++i) {
        if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
            selectedRoute = matchingRoutes[i];
            break;
        }
    }

    if (selectedRoute == -1) {
        cout << "\n\tInvalid route name. Please try again.\n";
        return;
    }

    // Find matching trains
    vector<int> matchingTrains;
    cout << "\n\tAvailable Trains for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < trains.size(); ++i) {
        if (trains[i].getRoute().getName() == routes[selectedRoute].getName()) {
            cout << "\t" << i + 1 << ". Train Number: " << trains[i].getTrainNumber() << " | Timing: " << trains[i].getTrainTiming() << " | Fare: ₹" << trains[i].getFare() << "\n";
            matchingTrains.push_back(i);
        }
    }

    if (matchingTrains.empty()) {
        cout << "\n\tNo trains available for the selected route.\n";
        return;
    }

    char sortOptionChoice;
    cout << "\n\tDo you want to sort the trains? (y/n): ";
    cin >> sortOptionChoice;

    if (sortOptionChoice == 'y' || sortOptionChoice == 'Y') {
        int sortOption;
        bool exitSorting = false;  // Flag to manage sorting loop

        // Keep asking the user for sorting until they choose to exit
        while (!exitSorting) {
            cout << "\n\tSort Trains By:\n";
            cout << "\t1. Time\n";
            cout << "\t2. Fare\n";
            cout << "\t3. Exit Sorting\n";
            cout << "\tEnter your choice: ";
            cin >> sortOption;

            switch (sortOption) {
                case 1: {
                    // Sorting by train timing (converted to minutes for proper comparison)
                    sort(matchingTrains.begin(), matchingTrains.end(), [this](int a, int b) {
                        return convertTimeToMinutes(trains[a].getTrainTiming()) < convertTimeToMinutes(trains[b].getTrainTiming());
                    });
                    cout << "\nTrains sorted by Time.\n";
                    break;
                }
                case 2: {
                    // Sorting by fare
                    sort(matchingTrains.begin(), matchingTrains.end(), [this](int a, int b) {
                        return trains[a].getFare() < trains[b].getFare();
                    });
                    cout << "\nTrains sorted by Fare.\n";
                    break;
                }
                case 3:
                    cout << "\nExiting sorting...\n";
                    exitSorting = true;  // Exit sorting loop, but not the booking function
                    break;
                default:
                    cout << "\nInvalid choice! Try again.\n";
                    continue; // Continue to the next iteration if the choice is invalid
            }

            // Display the sorted trains after each sort operation
            if (!exitSorting) {
                cout << "\nSorted Trains:\n";
                for (size_t i = 0; i < matchingTrains.size(); ++i) {
                    cout << "\t" << i + 1 << ". Train Number: " << trains[matchingTrains[i]].getTrainNumber()
                         << " | Timing: " << trains[matchingTrains[i]].getTrainTiming()
                         << " | Fare: ₹" << trains[matchingTrains[i]].getFare() << "\n";
                }
            }
        }
    } else {
        cout << "\nSorting skipped.\n";
    }

    // Select a train
    string selectedTrainString;
    cout << "\n\tSelect a Train (Enter the Train Number): ";
    cin.ignore();
    getline(cin, selectedTrainString);

    int selectedTrainIndex = -1;
    for (size_t i = 0; i < matchingTrains.size(); ++i) {
        if (trains[matchingTrains[i]].getTrainNumber() == selectedTrainString) {
            selectedTrainIndex = matchingTrains[i];
            break;
        }
    }

    if (selectedTrainIndex == -1) {
        cout << "\n\tInvalid train number. Please try again.\n";
        return;
    }

    // Display available seats
    trains[selectedTrainIndex].displayAvailableSeats();

    // Enter number of tickets
    cout << "\n\tEnter the number of tickets you want to book: ";
    cin >> numberOfTickets;

    if (cin.fail() || numberOfTickets < 1 || numberOfTickets > trains[selectedTrainIndex].getTotalSeats()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid number of tickets. Please try again.\n";
        return;
    }

    // Collect traveler details
    vector<pair<string, int>> travelers;
    for (int i = 1; i <= numberOfTickets; ++i) {
        string travelerName;
        int travelerAge;
        cout << "\n\tEnter Traveler " << i << "'s Name: ";
        cin.ignore();
        getline(cin, travelerName);
        cout << "\tEnter Traveler " << i << "'s Age: ";
        cin >> travelerAge;
        travelers.push_back({travelerName, travelerAge});
    }

    // Book tickets and select seats
    vector<TrainTicket> userTickets;
    for (int i = 0; i < numberOfTickets; ++i) {
        int selectedSeat;
        cout << "\n\tEnter Seat Number for Traveler " << (i + 1) << ": ";
        cin >> selectedSeat;

        if (cin.fail() || selectedSeat < 1 || selectedSeat > trains[selectedTrainIndex].getTotalSeats() ||
            !trains[selectedTrainIndex].reserveSeat(selectedSeat)) {
            cout << "\n\tInvalid or unavailable seat number. Booking failed for Traveler " << (i + 1) << ".\n";
            continue;
        }

        TrainTicket ticket(travelers[i].first, selectedSeat, routes[selectedRoute], trains[selectedTrainIndex]);
        userTickets.push_back(ticket);

        cout << "\n\t\t\tTicket for Traveler " << (i + 1) << ":\n";
        cout << "\t\t\tPassenger: " << ticket.getPassengerName() << " (Age: " << travelers[i].second << ")\n";
        cout << "\t\t\tTrain Number: " << trains[selectedTrainIndex].getTrainNumber() << "\n";
        cout << "\t\t\tRoute: " << ticket.getRoute().getName() << " (" << ticket.getRoute().getSource() << " to "
             << ticket.getRoute().getDestination() << ")\n";
        cout << "\t\t\tSeat Number: " << ticket.getSeatNumber() << "\n";
    }

    // Save tickets to file
    ofstream ticketsFile("train_tickets.txt", ios::app);
    if (ticketsFile.is_open()) {
        for (const auto& ticket : userTickets) {
            ticketsFile << username << "," << ticket.getPassengerName() << "," << ticket.getSeatNumber() << ","
                        << ticket.getRoute().getName() << "," << ticket.getTrain().getTrainNumber() << "\n";
        }
        ticketsFile.close();
    }

    // Print user tickets
    printUserTickets(username);
}*/

int convertTimeToMinutes(const string& timeStr) {
    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    return (hours * 60) + minutes;
}


    void printUserTickets(const string& username) {
        cout << "\n\tTickets for User: " << username << "\n";
        ifstream ticketsFile("train_tickets.txt");
        string line;
        while (getline(ticketsFile, line)) {
            stringstream ss(line);
            string storedUsername, passengerName, seatNumber, routeName, trainNumber;
            
            // Extract ticket details from the file
            getline(ss, storedUsername, ',');
            getline(ss, passengerName, ',');
            getline(ss, seatNumber, ',');
            getline(ss, routeName, ',');
            getline(ss, trainNumber, ',');
            
            // Check if the ticket belongs to the logged-in user
            if (storedUsername == username) {
                cout << "\n\t\t------ Ticket ------" << endl;
                cout << "\t\tPassenger: " << passengerName << endl;
                cout << "\t\tSeat Number: " << seatNumber << endl;
                cout << "\t\tRoute: " << routeName << endl;
                cout << "\t\tTrain Number: " << trainNumber << endl;
            }
        }
        ticketsFile.close();
    }

    void cancelTicket(const string& username) {
        ifstream ticketsFile("train_tickets.txt");
        if (!ticketsFile.is_open()) {
            cout << "\n\tError: Unable to open the tickets file.\n";
            return;
        }

        // Temporary vector to store all tickets for the logged-in user
        vector<string> updatedTickets;
        string line;
        bool ticketFound = false;

        // Display the tickets for the logged-in user
        cout << "\n\tTickets for User: " << username << "\n";
        int ticketIndex = 1;
        while (getline(ticketsFile, line)) {
            stringstream ss(line);
            string storedUsername, passengerName, seatNumber, routeName, trainNumber;
            
            // Extract ticket details from the file
            getline(ss, storedUsername, ',');
            getline(ss, passengerName, ',');
            getline(ss, seatNumber, ',');
            getline(ss, routeName, ',');
            getline(ss, trainNumber, ',');

            // Check if the ticket belongs to the logged-in user
            if (storedUsername == username) {
                cout << "\n\t\t------ Ticket " << ticketIndex++ << " ------" << endl;
                cout << "\t\tPassenger: " << passengerName << endl;
                cout << "\t\tSeat Number: " << seatNumber << endl;
                cout << "\t\tRoute: " << routeName << endl;
                cout << "\t\tTrain Number: " << trainNumber << endl;
                updatedTickets.push_back(line); // Save this ticket temporarily for removal or update
            }
        }
        ticketsFile.close();

        if (ticketIndex == 1) {
            cout << "\n\tNo tickets found for user: " << username << "\n";
            return;
        }

        // Ask the user which ticket to cancel
        int ticketToCancel;
        cout << "\n\tEnter the ticket number to cancel: ";
        cin >> ticketToCancel;

        if (ticketToCancel < 1 || ticketToCancel >= ticketIndex) {
            cout << "\n\tInvalid ticket number.\n";
            return;
        }

        // Remove the selected ticket from the list
        updatedTickets.erase(updatedTickets.begin() + ticketToCancel - 1);

        // Reopen the file and write the updated tickets
        ofstream outFile("train_tickets.txt", ios::trunc);
        if (!outFile.is_open()) {
            cout << "\n\tError: Unable to save updated tickets.\n";
            return;
        }

        for (const string& ticket : updatedTickets) {
            outFile << ticket << "\n";
        }
        outFile.close();

        cout << "\n\tTicket successfully canceled.\n";
    }

    void run() {
        while (true) {
            cout << "\n\t------ Welcome to the Train Reservation System ------\n\n";
            cout << "\t\t\t1. Register\n\t\t\t2. Log In\n\t\t\t3. Register Admin\n\t\t\t4. Log In Admin\n\t\t\t5. Exit\n";
            cout << "\n\t\t\tEnter your choice: ";
            int choice;
            cin >> choice;

            if (choice == 1) {
                // Inline registerUser functionality
                string username, password;
                cout << "\n\t\t\tEnter username: ";
                cin >> username;
                cout << "\t\t\tEnter password: ";
                password = getPassword();

                string filename = "train_user_credentials.txt";
                ofstream file(filename, ios::app);
                if (file.is_open()) {
                    file << username << "," << password << "\n";
                    file.close();
                    cout << "\n\t\tUser registered successfully!\n";
                } else {
                    cout << "\n\t\tError: Unable to open file for registration.\n";
                }
            } else if (choice == 2) {
    // Inline authenticateUser functionality
    string username, password;
    cout << "\n\t\t\tEnter username: ";
    cin >> username;
    cout << "\t\t\tEnter password: ";
    password = getPassword();

    string filename = "train_user_credentials.txt";
    ifstream file(filename);
    bool authenticated = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                string storedPassword = line.substr(commaPos + 1);
                if (storedUsername == username && storedPassword == password) {
                    authenticated = true;
                    break;
                }
            }
        }
        file.close();
    }

    if (authenticated) {
        cout << "\n\t\t\tLogged in successfully!\n";
        userMenu(username); // Uncomment and implement userMenu function as needed
    } else {
        cout << "\n\t\tAuthentication failed! Please check your username and password.\n";
        char choice;
        cout << "\n\t\tWould you like to change your password? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "\n\t\tPlease verify your username to change the password.\n";
            cout << "\t\t\tEnter username: ";
            cin >> username;
            changeUserPassword(username); // Implement this function to handle password changes
        }
    }
} else if (choice == 3) {
                // Inline registerUser functionality for admin
                string adminUsername, adminPassword;
                cout << "\n\t\t\tEnter new admin username: ";
                cin >> adminUsername;
                cout << "\t\t\tEnter new admin password: ";
                adminPassword = getPassword();

                string filename = "train_admin_credentials.txt";
                ofstream file(filename, ios::app);
                if (file.is_open()) {
                    file << adminUsername << "," << adminPassword << "\n";
                    file.close();
                    cout << "\n\t\tAdmin registered successfully!\n";
                } else {
                    cout << "\n\t\tError: Unable to open file for registration.\n";
                }
            } else if (choice == 4) {
    // Inline authenticateUser functionality for train admin
    string adminUsername, adminPassword;
    cout << "\n\t\t\tEnter train admin username: ";
    cin >> adminUsername;
    cout << "\t\t\tEnter train admin password: ";
    adminPassword = getPassword();

    string filename = "train_admin_credentials.txt";
    ifstream file(filename);
    bool authenticated = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                string storedPassword = line.substr(commaPos + 1);
                if (storedUsername == adminUsername && storedPassword == adminPassword) {
                    authenticated = true;
                    break;
                }
            }
        }
        file.close();
    }

    if (authenticated) {
        cout << "\n\t\t\tTrain admin logged in successfully!\n";
        adminMenu(); // Uncomment and implement adminMenu function as needed
    } else {
        cout << "\n\t\tAuthentication failed! Please check your train admin username and password.\n";
        char choice;
        cout << "\n\t\tWould you like to change your password? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "\n\t\tPlease verify your train admin username to change the password.\n";
            cout << "\t\t\tEnter train admin username: ";
            cin >> adminUsername;
            changeTrainAdminPassword(adminUsername);
        }
    }
}
 else if (choice == 5) {
                cout << "\n\t\tExiting the Train Reservation System. Goodbye!\n";
                break;
            } else {
                cout << "\n\t\tInvalid choice! Please try again.\n";
            }
        }
    }

    void userMenu(const string& username) {
        int choice = 0;
        while (true) {
            cout << "\n\t-----------  Welcome to the User Menu  ------------\n\n";
            cout << "\t\t\t1. Display Routes\n\t\t\t2. Display Trains\n\t\t\t3. Book Ticket\n\t\t\t4. Cancel Ticket\n\t\t\t5. Logout\n";
            cout << "\n\t\t\tEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                displayRoutes();
            } else if (choice == 2) {
                displayTrains();
            } else if (choice == 3) {
                bookTrainTicket(username);
            } else if (choice == 4) {
                cancelTicket(username);
            } else if (choice == 5) {
                cout << "\n\t\t\tLogged out successfully.\n";
                break;
            }
        }
    }

    private:
    vector<TrainUser> users;
    vector<TrainRoute> routes;
    vector<Train> trains;

    void adminMenu() {
        int choice = 0;
        while (true) {
            cout << "\n\t-----------  Welcome to the Admin Menu  ------------\n\n";
            cout << "\t\t\t1. Add Route\n\t\t\t2. Update Route\n\t\t\t3. Delete Route\n";
            cout << "\t\t\t4. Add Train\n\t\t\t5. Update Train\n\t\t\t6. Delete Train\n";
            cout << "\t\t\t7. Display Routes\n\t\t\t8. Display Trains\n\t\t\t9. Logout\n";
            cout << "\n\t\t\tEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    string name, source, destination;
                    int distance;
                    cout << "\n\t\tEnter Route Name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "\t\tEnter Route Source: ";
                    getline(cin, source);
                    cout << "\t\tEnter Route Destination: ";
                    getline(cin, destination);
                    cout << "\t\tEnter Route Distance: ";
                    cin >> distance;
                    addRoute(name, source, destination, distance);
                    break;
                }
                case 2: {
                    string name, newSource, newDestination;
                    int newDistance;
                    cout << "\n\t\tEnter Route Name to Update: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "\t\tEnter New Route Source: ";
                    getline(cin, newSource);
                    cout << "\t\tEnter New Route Destination: ";
                    getline(cin, newDestination);
                    cout << "\t\tEnter New Route Distance: ";
                    cin >> newDistance;
                    updateRoute(name, newSource, newDestination, newDistance);
                    break;
                }
                case 3: {
                    string name;
                    cout << "\n\t\tEnter Route Name to Delete: ";
                    cin.ignore();
                    getline(cin, name);
                    deleteRoute(name);
                    break;
                }
                case 4:{
    string trainNumber, routeName, trainTiming;
    double fare;
    int totalSeats;

    cout << "\n\t\tEnter Train Number: ";
    cin.ignore(); // Clear any leftover newline characters from previous inputs
    getline(cin, trainNumber);

    cout << "\t\tEnter Route Name: ";
    getline(cin, routeName);

    cout << "\t\tEnter Total Seats: ";
    cin >> totalSeats;

    // Clear input buffer to handle subsequent getline input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tEnter Train Timing (e.g., 10:30 AM): ";
    getline(cin, trainTiming);

    cout << "\t\tEnter Fare in rs: ";
    cin >> fare;

    // Clear input buffer for any further inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Call addTrain with all collected inputs
    addTrain(trainNumber, routeName, totalSeats, trainTiming, fare);
    break;
}

                case 5:{
    string trainNumber, newRouteName, newTrainTiming;
    int newTotalSeats;
    double newFare;

    cout << "\n\t\tEnter Train Number to Update: ";
    cin.ignore(); // Clear any leftover newline characters
    getline(cin, trainNumber);

    cout << "\t\tEnter New Route Name: ";
    getline(cin, newRouteName);

    cout << "\t\tEnter New Total Seats: ";
    cin >> newTotalSeats;

    // Clear input buffer to handle subsequent getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tEnter New Train Timing (e.g., 10:30 AM): ";
    getline(cin, newTrainTiming);

    cout << "\t\tEnter New Fare in rs: ";
    cin >> newFare;

    // Clear input buffer for any further inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Call the updateTrain function with collected inputs
    updateTrain(trainNumber, newRouteName, newTotalSeats, newTrainTiming, newFare);
    break;
}
                case 6: {
                    string trainNumber;
                    cout << "\n\t\tEnter Train Number to Delete: ";
                    cin.ignore();
                    getline(cin, trainNumber);
                    deleteTrain(trainNumber);
                    break;
                }
                case 7: {
                    cout << "\n\t-----------  Routes List  ------------\n";
                    ifstream routesFile("train_routes.txt");
                    string line;
                    if (routesFile.is_open()) {
                        while (getline(routesFile, line)) {
                            stringstream ss(line);
                            string name, source, destination;
                            int distance;
                            getline(ss, name, ',');
                            getline(ss, source, ',');
                            getline(ss, destination, ',');
                            ss >> distance;

                            cout << "\tRoute Name: " << name << "\n";
                            cout << "\tSource: " << source << "\n";
                            cout << "\tDestination: " << destination << "\n";
                            cout << "\tDistance: " << distance << " km\n";
                            cout << "\t--------------------------------------\n";
                        }
                        routesFile.close();
                    } else {
                        cout << "\t\tUnable to open routes file.\n";
                    }
                    break;
                }
                case 8: {
                    cout << "\n\t-----------  Trains List  ------------\n";
                    ifstream trainsFile("trains.txt");
                    string line;
                    if (trainsFile.is_open()) {
                        while (getline(trainsFile, line)) {
                            stringstream ss(line);
                            string trainNumber, routeName;
                            int totalSeats;
                            getline(ss, trainNumber, ',');
                            getline(ss, routeName, ',');
                            ss >> totalSeats;

                            cout << "\tTrain Number: " << trainNumber << "\n";
                            cout << "\tRoute Name: " << routeName << "\n";
                            cout << "\tTotal Seats: " << totalSeats << "\n";
                            cout << "\t------------------------------------\n";
                        }
                        trainsFile.close();
                    } else {
                        cout << "\t\tUnable to open trains file.\n";
                    }
                    break;
                }
                case 9: {
                    cout << "\n\t\t\tLogged out successfully.\n";
                    return; // Exit the menu
                }
                default:
                    cout << "\n\t\tInvalid choice! Please try again.\n";
            }
        }
    }

    void addRoute(const string& name, const string& source, const string& destination, int distance) {
        ofstream routesFile("train_routes.txt", ios::app);
        if (routesFile.is_open()) {
            routesFile << name << "," << source << "," << destination << "," << distance << "\n";
            routes.push_back(TrainRoute(name, source, destination, distance));
            routesFile.close();
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Update route
    void updateRoute(const string& name, const string& newSource, const string& newDestination, int newDistance) {
        ifstream routesFile("train_routes.txt");
        ofstream tempFile("temp_train_routes.txt");
        bool found = false;
        string line;

        if (routesFile.is_open() && tempFile.is_open()) {
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string routeName, source, destination;
                int distance;
                getline(ss, routeName, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;

                if (routeName == name) {
                    tempFile << routeName << "," << newSource << "," << newDestination << "," << newDistance << "\n";
                    found = true;
                    for (TrainRoute& route : routes) {
                        if (route.getName() == name) {
                            route = TrainRoute(name, newSource, newDestination, newDistance);
                            break;
                        }
                    }
                } else {
                    tempFile << line << "\n";
                }
            }
            routesFile.close();
            tempFile.close();
            remove("train_routes.txt");
            rename("temp_train_routes.txt", "train_routes.txt");

            if (found) {
                cout << "\t\tRoute updated successfully.\n";
            } else {
                cout << "\t\tRoute not found.\n";
            }
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Delete route
    void deleteRoute(const string& name) {
        ifstream routesFile("train_routes.txt");
        ofstream tempFile("temp_train_routes.txt");
        bool found = false;
        string line;

        if (routesFile.is_open() && tempFile.is_open()) {
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string routeName, source, destination;
                int distance;
                getline(ss, routeName, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;

                if (routeName == name) {
                    found = true;
                    routes.erase(remove_if(routes.begin(), routes.end(), [&](const TrainRoute& route) {
                        return route.getName() == name;
                    }), routes.end());
                } else {
                    tempFile << line << "\n";
                }
            }
            routesFile.close();
            tempFile.close();
            remove("train_routes.txt");
            rename("temp_train_routes.txt", "train_routes.txt");

            if (found) {
                cout << "\t\tRoute deleted successfully.\n";
            } else {
                cout << "\t\tRoute not found.\n";
            }
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

  void addTrain(const string& trainNumber, const string& routeName, int totalSeats, const string& trainTiming, double fare) {
    // Append data to the file and in-memory structure
    ofstream trainsFile("trains.txt", ios::app);
    if (trainsFile.is_open()) {
        trainsFile << trainNumber << "," << routeName << "," << totalSeats << "," << trainTiming << "," << fare << "\n";
        trainsFile.close();

        // Update the in-memory trains list
        bool routeFound = false;
        for (const TrainRoute& route : routes) {
            if (route.getName() == routeName) {
                trains.push_back(Train(trainNumber, route, totalSeats, trainTiming, fare));
                routeFound = true;
                cout << "\n\tTrain added successfully.\n";
                break;
            }
        }
        if (!routeFound) {
            cout << "\n\tRoute not found. Train added to the file but not linked to a valid route.\n";
        }
    } else {
        cout << "\t\tUnable to open trains file.\n";
    }
}
    void updateTrain(const string& trainNumber, const string& newRouteName, int newTotalSeats, const string& newTrainTiming, double newFare) {
    ifstream trainsFile("trains.txt");
    ofstream tempFile("temp_trains.txt");
    bool found = false;
    string line;

    if (trainsFile.is_open() && tempFile.is_open()) {
        while (getline(trainsFile, line)) {
            stringstream ss(line);
            string trainNum, routeName, trainTiming;
            int totalSeats;
            double fare;
            getline(ss, trainNum, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(1); // Ignore the comma
            getline(ss, trainTiming, ',');
            ss >> fare;

            if (trainNum == trainNumber) {
                tempFile << trainNum << "," << newRouteName << "," << newTotalSeats << "," << newTrainTiming << "," << newFare << "\n";
                found = true;

                // Update the vector storing trains
                for (Train& train : trains) {
                    if (train.getTrainNumber() == trainNumber) {
                        for (const TrainRoute& route : routes) {
                            if (route.getName() == newRouteName) {
                                train = Train(trainNumber, route, newTotalSeats, newTrainTiming, newFare);
                                break;
                            }
                        }
                        break;
                    }
                }
            } else {
                tempFile << line << "\n";
            }
        }

        trainsFile.close();
        tempFile.close();
        remove("trains.txt");
        rename("temp_trains.txt", "trains.txt");

        if (found) {
            cout << "\t\tTrain updated successfully.\n";
        } else {
            cout << "\t\tTrain not found.\n";
        }
    } else {
        cout << "\t\tUnable to open trains file.\n";
    }
}

    
   void deleteTrain(const string& trainNumber) {
    ifstream trainsFile("trains.txt");
    ofstream tempFile("temp_trains.txt");
    bool found = false;
    string line;

    if (trainsFile.is_open() && tempFile.is_open()) {
        while (getline(trainsFile, line)) {
            stringstream ss(line);
            string trainNum, routeName;
            int totalSeats;

            // Parsing the line
            getline(ss, trainNum, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;

            // Check if the current train matches the train to be deleted
            if (trainNum == trainNumber) {
                found = true; // Mark as found
                // Remove the train from the `trains` vector
                trains.erase(remove_if(trains.begin(), trains.end(), [&](const Train& train) {
                    return train.getTrainNumber() == trainNumber;
                }), trains.end());
            } else {
                // Write to the temporary file if not matching
                tempFile << line << "\n";
            }
        }

        // Close files and perform the replacement
        trainsFile.close();
        tempFile.close();
        remove("trains.txt");
        rename("temp_trains.txt", "trains.txt");

        // Output result to user
        if (found) {
            cout << "\t\tTrain deleted successfully.\n";
        } else {
            cout << "\t\tTrain not found.\n";
        }
    } else {
        // Error opening files
        cout << "\t\tUnable to open trains file.\n";
    }
}

};




















// Define the Route class with necessary member functions
class Route {
public:
    Route(const string& name, const string& source, const string& destination, int distance)
        : name(name), source(source), destination(destination), distance(distance) {}

    string getName() const { return name; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    int getDistance() const { return distance; }

private:
    string name;
    string source;
    string destination;
    int distance;
};



class Bus {
public:
    Bus(const string& busNumber, const Route& route, int totalSeats, const string& busTiming, double fare)
        : busNumber(busNumber), route(route), totalSeats(totalSeats), busTiming(busTiming), fare(fare) {
        seats.resize(totalSeats, false);
    }

    bool reserveSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats && !seats[seatNumber - 1]) {
            seats[seatNumber - 1] = true;
            return true;
        }
        return false;
    }

    bool cancelSeat(int seatNumber) {
        if (seatNumber >= 1 && seatNumber <= totalSeats && seats[seatNumber - 1]) {
            seats[seatNumber - 1] = false;
            return true;
        }
        return false;
    }

    

    void displayBusInfo() const {
        cout << "\n\t\t\tBus Number: " << busNumber << endl;
        cout << "\t\tRoute: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
        cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        cout << "\t\t\tTotal Seats: " << totalSeats << endl;
        cout << "\t\t\tBus Timing: " << busTiming << endl;
        cout << "\t\t\tFare: $" << fare << endl;
        cout << "\t\t----- Available Seat -----\n";
        bool flag = false;
        for (int i = 0; i < totalSeats; i++) {
            if (!seats[i]) {
                cout << "\t\t" << i + 1;
            } else {
                cout << "\t\tNA";
            }
            if (!flag) {
                cout << "\t";
                flag = true;
            } else {
                cout << "\n";
                flag = false;
            }
        }
        cout << endl;
    }

    void displayAvailableSeats() const {
        cout << "\t\t\tAvailable Seats on Bus " << busNumber << ":\n";
        for (int i = 0; i < totalSeats; ++i) {
            if (!seats[i]) {
                cout << "\t\t\tSeat " << i + 1 << ": Available\n";
            }
        }
    }

    void displayBusStatus() const {
        int reservedSeats = 0;
        for (int i = 0; i < totalSeats; ++i) {
            if (seats[i]) {
                reservedSeats++;
            }
        }

        cout << "Bus Status for Bus " << busNumber << ":\n";
        cout << "Total Seats: " << totalSeats << "\n";
        cout << "Reserved Seats: " << reservedSeats << "\n";
        cout << "Available Seats: " << totalSeats - reservedSeats << "\n";
    }

    string getBusNumber() const { return busNumber; }
    const Route& getRoute() const { return route; }
    int getTotalSeats() const { return totalSeats; }
    string getBusTiming() const { return busTiming; }
    double getFare() const { return fare; }

  
     


    



private:
    string busNumber;
    Route route;
    int totalSeats;
    string busTiming;
    double fare;
    vector<bool> seats;

    
};

int convertTimeToMinutes(const string& timeStr) {
    try {
        int hours = stoi(timeStr.substr(0, 2));
        int minutes = stoi(timeStr.substr(3, 2));
        return (hours * 60) + minutes;
    } catch (const std::invalid_argument& e) {
        cerr << "Invalid time format: " << timeStr << endl;
        return -1; // Return an error code
    } catch (const std::out_of_range& e) {
        cerr << "Time value out of range: " << timeStr << endl;
        return -1; // Return an error code
    }
}



// Define the Ticket class with necessary member functions
class Ticket {
public:
    Ticket(const string& passengerName, int seatNumber, Route& route, const Bus& bus)
        : passengerName(passengerName), seatNumber(seatNumber), route(route), bus(bus) {}

    string getPassengerName() const { return passengerName; }
    int getSeatNumber() const { return seatNumber; }
    const Route& getRoute() const { return route; }
    const Bus& getBus() const { return bus; }

private:
    string passengerName;
    int seatNumber;
    Route route;
    Bus bus;
};

// Define the User class with necessary member functions
class User {
public:
    User(const string& username, const string& password)
        : username(username), password(password) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    void addTicket(Ticket& newTicket) { tickets.push_back(newTicket); }
    //void removeTicket(int index) { tickets.erase(tickets.begin() + index - 1); }
    void removeTicket(int index) { tickets.erase(tickets.begin() + index - 1); }

    int numberOfTickets() const { return tickets.size(); }
    Ticket& getTicket(int index) { return tickets[index - 1]; }

private:
    string username;
    string password;
    vector<Ticket> tickets;
};







class BusReservationSystem1 {
public:
    BusReservationSystem1() {
        // Load routes from file
        ifstream routesFile("routes.txt");
        if (routesFile.is_open()) {
            string line;
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string name, source, destination;
                int distance;
                getline(ss, name, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;
                routes.push_back(Route(name, source, destination, distance));
            }
            routesFile.close();
        }

        

   ifstream busesFile("buses.txt");
    if (busesFile.is_open()) {
        string line;
        while (getline(busesFile, line)) {
            stringstream ss(line);
            string busNumber, routeName, busTiming;
            int totalSeats;
            double fare;

            getline(ss, busNumber, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(); // Ignore the comma
            getline(ss, busTiming, ',');
            ss >> fare;

            for (const Route& route : routes) {
                if (route.getName() == routeName) {
                    buses.push_back(Bus(busNumber, route, totalSeats, busTiming, fare));
                    break;
                }
            }
        }
        busesFile.close();
    }
}

    void registerUser(const string& username, const string& password) {
        users.push_back(User(username, password));
        cout << "\n\t\tUser registered successfully. Please login to continue!\n";
    }

    bool authenticateUser(const string& username, const string& password) {
        for (const User& user : users) {
            string lowercaseUsername = user.getUsername();
            string lowercaseInputUsername = username;
            transform(lowercaseUsername.begin(), lowercaseUsername.end(), lowercaseUsername.begin(), ::tolower);
            transform(lowercaseInputUsername.begin(), lowercaseInputUsername.end(), lowercaseInputUsername.begin(), ::tolower);

            if (lowercaseUsername == lowercaseInputUsername && user.getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    string getPassword() {
        string password;
        char ch;
        while (true) {
            ch = _getch(); 
            if (ch == '\r') { 
                cout << endl;
                break;
            } else if (ch == '\b' && !password.empty()) { 
                password.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                password += ch;
                cout << '*'; 
            }
        }
        return password;
    }

    // Function to change password
void changePassword(const string& username) {
    cout << "\n\t\t\tEnter new password: ";
    string newPassword = getPassword();
    string filename = "user_credentials.txt";
    ifstream file(filename);
    vector<string> lines;
    bool found = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                if (storedUsername == username) {
                    line = storedUsername + "," + newPassword;
                    found = true;
                }
            }
            lines.push_back(line);
        }
        file.close();
    }

    if (found) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const string& line : lines) {
                outFile << line << endl;
            }
            outFile.close();
            cout << "\n\t\tPassword changed successfully!\n";
        } else {
            cout << "\n\t\tUnable to open credentials file for writing.\n";
        }
    } else {
        cout << "\n\t\tUsername not found.\n";
    }
}



// Function to change admin password
void changeAdminPassword(const string& adminUsername) {
    cout << "\n\t\t\tEnter new password: ";
    string newPassword = getPassword();
    string filename = "admin_credentials.txt";
    ifstream file(filename);
    vector<string> lines;
    bool found = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                if (storedUsername == adminUsername) {
                    line = storedUsername + "," + newPassword;
                    found = true;
                }
            }
            lines.push_back(line);
        }
        file.close();
    }

    if (found) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const string& line : lines) {
                outFile << line << endl;
            }
            outFile.close();
            cout << "\n\t\tPassword changed successfully!\n";
        } else {
            cout << "\n\t\tUnable to open credentials file for writing.\n";
        }
    } else {
        cout << "\n\t\tAdmin username not found.\n";
    }
}

    User& findUser(const string& username) {
        for (User& user : users) {
            if (user.getUsername() == username) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }

    /*void displayRoutes() const {
        cout << "\n\t\t------ Available Routes ------\n";
        for (const Route& route : routes) {
            cout << "\n\t\tRoute Name: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
            cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        }
    }*/

   void displayRoutes() {
    string source, destination;
    set<string> locations; // Set to store unique locations

    // Populate the locations set
    for (const auto& route : routes) {
        string source = route.getSource();
        source.erase(0, source.find_first_not_of(" \t")); // Trim leading spaces
        source.erase(source.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(source);

        string destination = route.getDestination();
        destination.erase(0, destination.find_first_not_of(" \t")); // Trim leading spaces
        destination.erase(destination.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(destination);
    }

    cout << "\n\t-----------  Routes List  ------------\n";
    ifstream routesFile("routes.txt");
    string line;
    if (routesFile.is_open()) {
        while (getline(routesFile, line)) {
            stringstream ss(line);
            string name, source, destination;
            int distance;
            getline(ss, name, ',');
            getline(ss, source, ',');
            getline(ss, destination, ',');
            ss >> distance;

            cout << "\tRoute Name: " << name << "\n";
            cout << "\tSource: " << source << "\n";
            cout << "\tDestination: " << destination << "\n";
            cout << "\tDistance: " << distance << " km\n";
            cout << "\t--------------------------------------\n";
        }
        routesFile.close();
    } else {
        cout << "\t\tUnable to open routes file.\n";
    }

    // New functionality to display available locations and routes
    cout << "\n\tAvailable Locations:\n";
    for (const string& location : locations) {
        cout << "\t- " << location << "\n";
    }

    cout << "\n\tEnter Source: ";
    cin.ignore();
    getline(cin, source);
    cout << "\tEnter Destination: ";
    getline(cin, destination);

    vector<int> matchingRoutes;
    cout << "\n\tAvailable Routes:\n";
    for (size_t i = 0; i < routes.size(); ++i) {
        if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
            cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
            matchingRoutes.push_back(i);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "\n\tNo routes available for the entered source and destination.\n";
        return;
    }

    string selectedRouteName;
    cout << "\n\tSelect a Route (Enter the Route Name): ";
    getline(cin, selectedRouteName);

    int selectedRoute = -1;
    for (size_t i = 0; i < matchingRoutes.size(); ++i) {
        if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
            selectedRoute = matchingRoutes[i];
            break;
        }
    }

    if (selectedRoute == -1) {
        cout << "\n\tInvalid route name. Please try again.\n";
        return;
    }

    vector<int> matchingBuses;
    cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < buses.size(); ++i) {
        if (buses[i].getRoute().getName() == routes[selectedRoute].getName()) {
            cout << "\t" << i + 1 << ". Bus Number: " << buses[i].getBusNumber() << "\n";
            matchingBuses.push_back(i);
        }
    }

    if (matchingBuses.empty()) {
        cout << "\n\tNo buses available for the selected route.\n";
        return;
    }
}

    

   void displayBuses() const {
    cout << "\n\t-----------  Buses List  ------------\n";
    ifstream busesFile("buses.txt");
    string line;

    if (busesFile.is_open()) {
        while (getline(busesFile, line)) {
            stringstream ss(line);
            string busNumber, routeName, busTiming;
            int totalSeats;
            double fare;

            // Parse the line
            getline(ss, busNumber, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(); // Ignore the comma
            getline(ss, busTiming, ',');
            ss >> fare;

            // Display the parsed information
            cout << "\tBus Number: " << busNumber << "\n";
            cout << "\tRoute Name: " << routeName << "\n";
            cout << "\tTotal Seats: " << totalSeats << "\n";
            cout << "\tBus Timing: " << busTiming << "\n";
            cout << "\tFare: " << fare << "\n";
            cout << "\t------------------------------------\n";
        }
        busesFile.close();
    } else {
        cout << "\t\tUnable to open buses file.\n";
    }
}


    void displayBusesForRoute(int selectedRoute) const {
        cout << "\t\t\tBuses available for Route " << routes[selectedRoute - 1].getName() << ":\n";
        for (const Bus& bus : buses) {
            if (bus.getRoute().getName() == routes[selectedRoute - 1].getName()) {
                bus.displayBusInfo();
                cout << endl;
            }
        }
    }


void bookTicket(const string& username) {


    string source, destination;
    int numberOfTickets;

 
    set<string> locations;
    for (const auto& route : routes) {
        string routeSource = route.getSource();
        routeSource.erase(0, routeSource.find_first_not_of(" \t"));
        routeSource.erase(routeSource.find_last_not_of(" \t") + 1);
        locations.insert(routeSource);

        string routeDestination = route.getDestination();
        routeDestination.erase(0, routeDestination.find_first_not_of(" \t"));
        routeDestination.erase(routeDestination.find_last_not_of(" \t") + 1);
        locations.insert(routeDestination);
    }

    cout << "\n\tAvailable Locations:\n";
    for (const string& location : locations) {

        cout << "\t- " << location << "\n";

    }

    cout << "\n\tEnter Source: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear previous input
    getline(cin, source);
    cout << "\tEnter Destination: ";
    getline(cin, destination);

    vector<int> matchingRoutes;
    cout << "\n\tAvailable Routes:\n";
    for (size_t i = 0; i < routes.size(); ++i) {
        if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
            cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
            matchingRoutes.push_back(i);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "\n\tNo routes available for the entered source and destination.\n";
        return;
    }

    string selectedRouteName;
    cout << "\n\tSelect a Route (Enter the Route Name): ";
    getline(cin, selectedRouteName);

    int selectedRoute = -1;
    for (size_t i = 0; i < matchingRoutes.size(); ++i) {
        if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
            selectedRoute = matchingRoutes[i];
            break;
        }
    }

    if (selectedRoute == -1) {
        cout << "\n\tInvalid route name. Please try again.\n";
        return;
    }

    vector<int> matchingBuses;
    cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < buses.size(); ++i) {
        if (buses[i].getRoute().getName() == routes[selectedRoute].getName()) {
            matchingBuses.push_back(i);
        }
    }

    if (matchingBuses.empty()) {
        cout << "\n\tNo buses available for the selected route.\n";
        return;
    }

    cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < matchingBuses.size(); ++i) {
        cout << "\t" << i + 1 << ". Bus Number: " << buses[matchingBuses[i]].getBusNumber()
             << " | Timing: " << buses[matchingBuses[i]].getBusTiming()
             << " | Fare: ₹" << buses[matchingBuses[i]].getFare() << "\n";
    }

    char sortOptionChoice;
    cout << "\n\tDo you want to sort the buses? (y/n): ";
    cin >> sortOptionChoice;

    if (sortOptionChoice == 'y' || sortOptionChoice == 'Y') {
        int sortOption;
        bool exitSorting = false;  // Flag to manage sorting loop

        // Keep asking the user for sorting until they choose to exit
        while (!exitSorting) {
            cout << "\n\tSort Buses By:\n";
            cout << "\t1. Time\n";
            cout << "\t2. Fare\n";
            cout << "\t3. Exit Sorting\n";
            cout << "\tEnter your choice: ";
            cin >> sortOption;

            switch (sortOption) {
                case 1: {
                    // Sorting by bus timing (converted to minutes for proper comparison)
                    sort(matchingBuses.begin(), matchingBuses.end(), [this](int a, int b) {
                        return convertTimeToMinutes(buses[a].getBusTiming()) < convertTimeToMinutes(buses[b].getBusTiming());
                    });
                    cout << "\nBuses sorted by Time.\n";
                    break;
                }
                case 2: {
                    // Sorting by fare
                    sort(matchingBuses.begin(), matchingBuses.end(), [this](int a, int b) {
                        return buses[a].getFare() < buses[b].getFare();
                    });
                    cout << "\nBuses sorted by Fare.\n";
                    break;
                }
                case 3:
                    cout << "\nExiting sorting...\n";
                    exitSorting = true;  // Exit sorting loop, but not the booking function
                    break;
                default:
                    cout << "\nInvalid choice! Try again.\n";
                    continue; // Continue to the next iteration if the choice is invalid
            }

            // Display the sorted buses after each sort operation
            if (!exitSorting) {
                cout << "\nSorted Buses:\n";
                for (size_t i = 0; i < matchingBuses.size(); ++i) {
                    cout << "\t" << i + 1 << ". Bus Number: " << buses[matchingBuses[i]].getBusNumber()
                         << " | Timing: " << buses[matchingBuses[i]].getBusTiming()
                         << " | Fare: ₹" << buses[matchingBuses[i]].getFare() << "\n";
                }
            }
        }
    } else {
        cout << "\nSorting skipped.\n";
    }
    

    // Select bus
    string selectedBusString;
    cout << "\n\tSelect a Bus (Enter the Bus Number): ";
    cin.ignore();
    getline(cin, selectedBusString);

    int selectedBusIndex = -1;
    for (size_t i = 0; i < matchingBuses.size(); ++i) {
        if (buses[matchingBuses[i]].getBusNumber() == selectedBusString) {
            selectedBusIndex = matchingBuses[i];
            break;
        }
    }

    if (selectedBusIndex == -1) {
        cout << "\n\tInvalid bus number. Please try again.\n";
        return;
    }

    buses[selectedBusIndex].displayAvailableSeats();

    cout << "\n\tEnter the number of tickets you want to book: ";
    cin >> numberOfTickets;

    if (cin.fail() || numberOfTickets < 1 || numberOfTickets > buses[selectedBusIndex].getTotalSeats()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid number of tickets. Please try again.\n";
        return;
    }

    vector<pair<string, int>> travelers;
    for (int i = 1; i <= numberOfTickets; ++i) {
        string travelerName;
        int travelerAge;
        cout << "\n\tEnter Traveler " << i << "'s Name: ";
        cin.ignore();
        getline(cin, travelerName);
        cout << "\tEnter Traveler " << i << "'s Age: ";
        cin >> travelerAge;

        travelers.push_back({travelerName, travelerAge});
    }

    vector<Ticket> userTickets;
    for (int i = 0; i < numberOfTickets; ++i) {
        int selectedSeat;
        cout << "\n\tEnter Seat Number for Traveler " << (i + 1) << ": ";
        cin >> selectedSeat;

        if (cin.fail() || selectedSeat < 1 || selectedSeat > buses[selectedBusIndex].getTotalSeats() ||
            !buses[selectedBusIndex].reserveSeat(selectedSeat)) {
            cout << "\n\tInvalid or unavailable seat number. Booking failed for Traveler " << (i + 1) << ".\n";
            continue;
        }

        Ticket ticket(travelers[i].first, selectedSeat, routes[selectedRoute], buses[selectedBusIndex]);
        userTickets.push_back(ticket);

        cout << "\n\t\t\tTicket for Traveler " << (i + 1) << ":\n";
        cout << "\t\t\tPassenger: " << ticket.getPassengerName() << " (Age: " << travelers[i].second << ")\n";
        cout << "\t\t\tBus Number: " << buses[selectedBusIndex].getBusNumber() << "\n";
        cout << "\t\t\tRoute: " << ticket.getRoute().getName() << " (" << ticket.getRoute().getSource() << " to "
             << ticket.getRoute().getDestination() << ")\n";
        cout << "\t\t\tSeat Number: " << ticket.getSeatNumber() << "\n";
    }

   

    ofstream ticketsFile("tickets.txt", ios::app);
    if (ticketsFile.is_open()) {
        for (const auto& ticket : userTickets) {
            ticketsFile << username << "," << ticket.getPassengerName() << "," << ticket.getSeatNumber() << ","
                        << ticket.getRoute().getName() << "," << ticket.getBus().getBusNumber() << "\n";
        }
        ticketsFile.close();
    }

    

    printUserTickets(username);
}

int convertTimeToMinutes(const string& timeStr) {
    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    return (hours * 60) + minutes;
}





void printUserTickets(const string& username) {
    cout << "\n\tTickets for User: " << username << "\n";
    ifstream ticketsFile("tickets.txt");
    string line;
    while (getline(ticketsFile, line)) {
        stringstream ss(line);
        string storedUsername, passengerName, seatNumber, routeName, busNumber;
        
        // Extract ticket details from the file
        getline(ss, storedUsername, ',');
        getline(ss, passengerName, ',');
        getline(ss, seatNumber, ',');
        getline(ss, routeName, ',');
        getline(ss, busNumber, ',');
        
        // Check if the ticket belongs to the logged-in user
        if (storedUsername == username) {
            cout << "\n\t\t------ Ticket ------" << endl;
            cout << "\t\tPassenger: " << passengerName << endl;
            cout << "\t\tSeat Number: " << seatNumber << endl;
            cout << "\t\tRoute: " << routeName << endl;
            cout << "\t\tBus Number: " << busNumber << endl;
        }
    }
    ticketsFile.close();
}





void cancelTicket(const string& username) {
    ifstream ticketsFile("tickets.txt");
    if (!ticketsFile.is_open()) {
        cout << "\n\tError: Unable to open the tickets file.\n";
        return;
    }

    // Temporary vector to store all tickets for the logged-in user
    vector<string> updatedTickets;
    string line;
    bool ticketFound = false;
    int selectedBusIndex = -1; // To store the index of the bus
    int seatNumberToRelease = -1; // To store the seat number to release
    vector<string> userTickets;  // To store the tickets for this user

    // Display the tickets for the logged-in user
    cout << "\n\tTickets for User: " << username << "\n";
    int ticketIndex = 1;
    while (getline(ticketsFile, line)) {
        stringstream ss(line);
        string storedUsername, passengerName, seatNumber, routeName, busNumber;
        
        // Extract ticket details from the file
        getline(ss, storedUsername, ',');
        getline(ss, passengerName, ',');
        getline(ss, seatNumber, ',');
        getline(ss, routeName, ',');
        getline(ss, busNumber, ',');

        // Check if the ticket belongs to the logged-in user
        if (storedUsername == username) {
            cout << "\n\t\t------ Ticket " << ticketIndex++ << " ------" << endl;
            cout << "\t\tPassenger: " << passengerName << endl;
            cout << "\t\tSeat Number: " << seatNumber << endl;
            cout << "\t\tRoute: " << routeName << endl;
            cout << "\t\tBus Number: " << busNumber << endl;

            // Store this ticket in the user's list of tickets
            userTickets.push_back(line);

            // Capture the seat number and bus number for cancellation
            seatNumberToRelease = stoi(seatNumber);  // Convert seat number to integer
            // Find the bus index by matching bus number
            for (size_t i = 0; i < buses.size(); ++i) {
                if (buses[i].getBusNumber() == busNumber) {
                    selectedBusIndex = i;
                    break;
                }
            }
        } else {
            // If it's not the current user's ticket, add it to the updatedTickets list
            updatedTickets.push_back(line);
        }
    }
    ticketsFile.close();

    if (userTickets.empty()) {
        cout << "\n\tNo tickets found for user: " << username << "\n";
        return;
    }

    // Ask the user which ticket to cancel
    int ticketToCancel;
    cout << "\n\tEnter the ticket number to cancel: ";
    cin >> ticketToCancel;

    if (ticketToCancel < 1 || ticketToCancel > userTickets.size()) {
        cout << "\n\tInvalid ticket number.\n";
        return;
    }

    // Remove the selected ticket from the user's list
    userTickets.erase(userTickets.begin() + ticketToCancel - 1);

    // Reopen the file and write the updated tickets for all users, excluding the canceled ticket
    ofstream outFile("tickets.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "\n\tError: Unable to save updated tickets.\n";
        return;
    }

    // Write back the updated tickets for all users (excluding the canceled ticket)
    for (const string& ticket : updatedTickets) {
        outFile << ticket << "\n";
    }

    // Write back the remaining tickets for the current user
    for (const string& ticket : userTickets) {
        outFile << ticket << "\n";
    }

    outFile.close();

    // Debugging: Check if the file has been written correctly
    cout << "\n\tTickets file updated successfully. Releasing seat: " << seatNumberToRelease << "\n";

    // Update the seat availability on the bus
    if (selectedBusIndex != -1) {
        // Update the seats_status file after canceling the ticket
        updateSeatStatus(selectedBusIndex, seatNumberToRelease);
        cout << "\n\tSeat number " << seatNumberToRelease << " is now available.\n";
    }

    cout << "\n\tTicket successfully canceled.\n";
}

// Function to update seat availability in the seats_status file
void updateSeatStatus(int busIndex, int seatNumberToRelease) {
    ifstream seatsFile("seats_status.txt");
    if (!seatsFile.is_open()) {
        cout << "\n\tError: Unable to open the seats_status file.\n";
        return;
    }

    vector<string> seatStatuses;
    string line;

    // Read the seat statuses for all buses
    while (getline(seatsFile, line)) {
        stringstream ss(line);
        string busNumber, seatStatus;
        getline(ss, busNumber, ',');
        getline(ss, seatStatus, ',');

        // If we find the bus matching the selected one, update the seat status
        if (busNumber == buses[busIndex].getBusNumber()) {
            // Check if this is the seat we need to release
            if (stoi(seatStatus) == seatNumberToRelease) {
                seatStatus = "available"; // Mark the seat as available
            }
        }

        // Add the updated or unchanged status to the list
        seatStatuses.push_back(busNumber + "," + seatStatus);
    }
    seatsFile.close();

    // Write back the updated seat statuses to the file
    ofstream outFile("seats_status.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "\n\tError: Unable to save updated seat statuses.\n";
        return;
    }

    for (const string& status : seatStatuses) {
        outFile << status << "\n";
    }

    outFile.close();
}








void run() {
    while (true) {
        cout << "\n\t------ Welcome to the Bus Reservation System ------\n\n";
        cout << "\t\t\t1. Register\n\t\t\t2. Log In\n\t\t\t3. Register Admin\n\t\t\t4. Log In Admin\n\t\t\t5. Exit\n";
        cout << "\n\t\t\tEnter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Inline registerUser functionality
            string username, password;
            cout << "\n\t\t\tEnter username: ";
            cin >> username;
            cout << "\t\t\tEnter password: ";
            password = getPassword();

            string filename = "user_credentials.txt";
            ofstream file(filename, ios::app);
            if (file.is_open()) {
                file << username << "," << password << "\n";
                file.close();
                cout << "\n\t\tUser registered successfully!\n";
            } else {
                cout << "\n\t\tError: Unable to open file for registration.\n";
            }
        } else if (choice == 2) {
            // Inline authenticateUser functionality
            string username, password;
            cout << "\n\t\t\tEnter username: ";
            cin >> username;
            cout << "\t\t\tEnter password: ";
            password = getPassword();

            string filename = "user_credentials.txt";
            ifstream file(filename);
            bool authenticated = false;

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    size_t commaPos = line.find(',');
                    if (commaPos != string::npos) {
                        string storedUsername = line.substr(0, commaPos);
                        string storedPassword = line.substr(commaPos + 1);
                        if (storedUsername == username && storedPassword == password) {
                            authenticated = true;
                            break;
                        }
                    }
                }
                file.close();
            }

                 if (authenticated) {
                cout << "\n\t\t\tLogged in successfully!\n";
                userMenu(username);
            } else {
                cout << "\n\t\tAuthentication failed! Please check your username and password.\n";
                char choice;
                cout << "\n\t\tWould you like to change your password? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    cout << "\n\t\tPlease verify your username to change the password.\n";
                    cout << "\t\t\tEnter username: ";
                    cin >> username;
                    changePassword(username);
                }
            }
        }
       
       
       
       
        else if (choice == 3) {
            // Inline registerUser functionality for admin
            string adminUsername, adminPassword;
            cout << "\n\t\t\tEnter new admin username: ";
            cin >> adminUsername;
            cout << "\t\t\tEnter new admin password: ";
            adminPassword = getPassword();

            string filename = "admin_credentials.txt";
            ofstream file(filename, ios::app);
            if (file.is_open()) {
                file << adminUsername << "," << adminPassword << "\n";
                file.close();
                cout << "\n\t\tAdmin registered successfully!\n";
            } else {
                cout << "\n\t\tError: Unable to open file for registration.\n";
            }
        } else if (choice == 4) {
            // Inline authenticateUser functionality for admin
            string adminUsername, adminPassword;
            cout << "\n\t\t\tEnter admin username: ";
            cin >> adminUsername;
            cout << "\t\t\tEnter admin password: ";
            adminPassword = getPassword();

            string filename = "admin_credentials.txt";
            ifstream file(filename);
            bool authenticated = false;

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    size_t commaPos = line.find(',');
                    if (commaPos != string::npos) {
                        string storedUsername = line.substr(0, commaPos);
                        string storedPassword = line.substr(commaPos + 1);
                        if (storedUsername == adminUsername && storedPassword == adminPassword) {
                            authenticated = true;
                            break;
                        }
                    }
                }
                file.close();
            }

           
         if (authenticated) {
                cout << "\n\t\t\tAdmin logged in successfully!\n";
                 adminMenu(); // Uncomment and implement adminMenu function as needed
            } else {
                cout << "\n\t\tAuthentication failed! Please check your admin username and password.\n";
                char choice;
                cout << "\n\t\tWould you like to change your password? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    cout << "\n\t\tPlease verify your admin username to change the password.\n";
                    cout << "\t\t\tEnter admin username: ";
                    cin >> adminUsername;
                    changeAdminPassword(adminUsername);
                }
            }
        }
       
       
        else if (choice == 5) {
            cout << "\n\t\tExiting the Bus Reservation System. Goodbye!\n";
            break;
        } else {
            cout << "\n\t\tInvalid choice! Please try again.\n";
        }
    }
}




    void userMenu(const string& username) {
        int choice = 0;
        while (true) {
            cout << "\n\t-----------  Welcome to the User Menu  ------------\n\n";
            cout << "\t\t\t1. Display Routes\n\t\t\t2. Display Buses\n\t\t\t3. Book Ticket\n\t\t\t4. Cancel Ticket\n\t\t\t5. Logout\n";
            cout << "\n\t\t\tEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                displayRoutes();
            } else if (choice == 2) {
                displayBuses();
            } else if (choice == 3) {
                bookTicket(username);
            } else if (choice == 4) {
                cancelTicket(username);
            } else if (choice == 5) {
                cout << "\n\t\t\tLogged out successfully.\n";
                break;
            }
        }
    }

    private:
    vector<User> users;
    vector<Route> routes;
    vector<Bus> buses;


   
   
   void adminMenu() {
    int choice = 0;
    while (true) {
        cout << "\n\t-----------  Welcome to the Admin Menu  ------------\n\n";
        cout << "\t\t\t1. Add Route\n\t\t\t2. Update Route\n\t\t\t3. Delete Route\n";
        cout << "\t\t\t4. Add Bus\n\t\t\t5. Update Bus\n\t\t\t6. Delete Bus\n";
        cout << "\t\t\t7. Display Routes\n\t\t\t8. Display Buses\n\t\t\t9. Logout\n";
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, source, destination;
                int distance;
                cout << "\n\t\tEnter Route Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "\t\tEnter Route Source: ";
                getline(cin, source);
                cout << "\t\tEnter Route Destination: ";
                getline(cin, destination);
                cout << "\t\tEnter Route Distance: ";
                cin >> distance;
                addRoute(name, source, destination, distance);
                break;
            }
            case 2: {
                string name, newSource, newDestination;
                int newDistance;
                cout << "\n\t\tEnter Route Name to Update: ";
                cin.ignore();
                getline(cin, name);
                cout << "\t\tEnter New Route Source: ";
                getline(cin, newSource);
                cout << "\t\tEnter New Route Destination: ";
                getline(cin, newDestination);
                cout << "\t\tEnter New Route Distance: ";
                cin >> newDistance;
                updateRoute(name, newSource, newDestination, newDistance);
                break;
            }
            case 3: {
                string name;
                cout << "\n\t\tEnter Route Name to Delete: ";
                cin.ignore();
                getline(cin, name);
                deleteRoute(name);
                break;
            }
            case 4: {
              string busNumber, routeName, busTiming;
double fare;
int totalSeats;

cout << "\n\t\tEnter Bus Number: ";
cin.ignore(); // Clear any leftover newline characters from previous inputs
getline(cin, busNumber);

cout << "\t\tEnter Route Name: ";
getline(cin, routeName);

cout << "\t\tEnter Total Seats: ";
cin >> totalSeats;

// Clear input buffer to handle subsequent getline input
cin.ignore(numeric_limits<streamsize>::max(), '\n');

cout << "\t\tEnter Bus Timing (e.g., 10:30 AM): ";
getline(cin, busTiming);

cout << "\t\tEnter Fare in rs: ";
cin >> fare;

// Clear input buffer for any further inputs
cin.ignore(numeric_limits<streamsize>::max(), '\n');

// Call addBus with all collected inputs
addBus(busNumber, routeName, totalSeats, busTiming, fare);
break;

            }
            case 5: {
                

                 string busNumber, newRouteName, newBusTiming;
    int newTotalSeats;
    double newFare;

    cout << "\n\t\tEnter Bus Number to Update: ";
    cin.ignore(); // Clear any leftover newline characters
    getline(cin, busNumber);

    cout << "\t\tEnter New Route Name: ";
    getline(cin, newRouteName);

    cout << "\t\tEnter New Total Seats: ";
    cin >> newTotalSeats;

    // Clear input buffer to handle subsequent getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tEnter New Bus Timing (e.g., 10:30 AM): ";
    getline(cin, newBusTiming);

    cout << "\t\tEnter New Fare in rs: ";
    cin >> newFare;

    // Call the updateBus function with collected inputs
    updateBus(busNumber, newRouteName, newTotalSeats, newBusTiming, newFare);
    break;
            }
            case 6: {
                string busNumber;
                cout << "\n\t\tEnter Bus Number to Delete: ";
                cin.ignore();
                getline(cin, busNumber);
                deleteBus(busNumber);
                break;
            }
            case 7: {

                string source, destination;
    int numberOfTickets;

    set<string> locations; // Set to store unique locations
    for (const auto& route : routes) {
        string source = route.getSource();
        source.erase(0, source.find_first_not_of(" \t")); // Trim leading spaces
        source.erase(source.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(source);

        string destination = route.getDestination();
        destination.erase(0, destination.find_first_not_of(" \t")); // Trim leading spaces
        destination.erase(destination.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(destination);
    }
                
                cout << "\n\t-----------  Routes List  ------------\n";
                ifstream routesFile("routes.txt");
                string line;
                if (routesFile.is_open()) {
                    while (getline(routesFile, line)) {
                        stringstream ss(line);
                        string name, source, destination;
                        int distance;
                        getline(ss, name, ',');
                        getline(ss, source, ',');
                        getline(ss, destination, ',');
                        ss >> distance;

                        cout << "\tRoute Name: " << name << "\n";
                        cout << "\tSource: " << source << "\n";
                        cout << "\tDestination: " << destination << "\n";
                        cout << "\tDistance: " << distance << " km\n";
                        cout << "\t--------------------------------------\n";
                    }
                    routesFile.close();
                } else {
                    cout << "\t\tUnable to open routes file.\n";
                }

                // New functionality to display available locations and routes
                cout << "\n\tAvailable Locations:\n";
                for (const string& location : locations) {
                    cout << "\t- " << location << "\n";
                }

                cout << "\n\tEnter Source: ";
                cin.ignore();
                getline(cin, source);
                cout << "\tEnter Destination: ";
                getline(cin, destination);

                vector<int> matchingRoutes;
                cout << "\n\tAvailable Routes:\n";
                for (size_t i = 0; i < routes.size(); ++i) {
                    if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
                        cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
                        matchingRoutes.push_back(i);
                    }
                }

                if (matchingRoutes.empty()) {
                    cout << "\n\tNo routes available for the entered source and destination.\n";
                    break;
                }

                string selectedRouteName;
                cout << "\n\tSelect a Route (Enter the Route Name): ";
                getline(cin, selectedRouteName);

                int selectedRoute = -1;
                for (size_t i = 0; i < matchingRoutes.size(); ++i) {
                    if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
                        selectedRoute = matchingRoutes[i];
                        break;
                    }
                }

                if (selectedRoute == -1) {
                    cout << "\n\tInvalid route name. Please try again.\n";
                    break;
                }

                vector<int> matchingBuses;
                cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
                for (size_t i = 0; i < buses.size(); ++i) {
                    if (buses[i].getRoute().getName() == routes[selectedRoute].getName()) {
                        cout << "\t" << i + 1 << ". Bus Number: " << buses[i].getBusNumber() << "\n";
                        matchingBuses.push_back(i);
                    }
                }

                if (matchingBuses.empty()) {
                    cout << "\n\tNo buses available for the selected route.\n";
                    break;
                }

                break;
                
                
             
            }
            case 8: {
                cout << "\n\t-----------  Buses List  ------------\n";
                ifstream busesFile("buses.txt");
                string line;
                if (busesFile.is_open()) {
                    while (getline(busesFile, line)) {
                        stringstream ss(line);
                        string busNumber, routeName;
                        int totalSeats;
                        getline(ss, busNumber, ',');
                        getline(ss, routeName, ',');
                        ss >> totalSeats;

                        cout << "\tBus Number: " << busNumber << "\n";
                        cout << "\tRoute Name: " << routeName << "\n";
                        cout << "\tTotal Seats: " << totalSeats << "\n";
                        cout << "\t------------------------------------\n";
                    }
                    busesFile.close();
                } else {
                    cout << "\t\tUnable to open buses file.\n";
                }
                break;
            }
            case 9: {
                cout << "\n\t\t\tLogged out successfully.\n";
                return; // Exit the menu
            }
            default:
                cout << "\n\t\tInvalid choice! Please try again.\n";
        }
    }
}


  
    void addRoute(const string& name, const string& source, const string& destination, int distance) {
        ofstream routesFile("routes.txt", ios::app);
        if (routesFile.is_open()) {
            routesFile << name << "," << source << "," << destination << "," << distance << "\n";
            routes.push_back(Route(name, source, destination, distance));
            routesFile.close();
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Update route
    void updateRoute(const string& name, const string& newSource, const string& newDestination, int newDistance) {
        ifstream routesFile("routes.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        string line;

        if (routesFile.is_open() && tempFile.is_open()) {
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string routeName, source, destination;
                int distance;
                getline(ss, routeName, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;

                if (routeName == name) {
                    tempFile << routeName << "," << newSource << "," << newDestination << "," << newDistance << "\n";
                    found = true;
                    for (Route& route : routes) {
                        if (route.getName() == name) {
                            route = Route(name, newSource, newDestination, newDistance);
                            break;
                        }
                    }
                } else {
                    tempFile << line << "\n";
                }
            }
            routesFile.close();
            tempFile.close();
            remove("routes.txt");
            rename("temp.txt", "routes.txt");

            if (found) {
                cout << "\t\tRoute updated successfully.\n";
            } else {
                cout << "\t\tRoute not found.\n";
            }
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Delete route
    void deleteRoute(const string& name) {
        ifstream routesFile("routes.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        string line;

        if (routesFile.is_open() && tempFile.is_open()) {
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string routeName, source, destination;
                int distance;
                getline(ss, routeName, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;

                if (routeName == name) {
                    found = true;
                    routes.erase(remove_if(routes.begin(), routes.end(), [&](const Route& route) {
                        return route.getName() == name;
                    }), routes.end());
                } else {
                    tempFile << line << "\n";
                }
            }
            routesFile.close();
            tempFile.close();
            remove("routes.txt");
            rename("temp.txt", "routes.txt");

            if (found) {
                cout << "\t\tRoute deleted successfully.\n";
            } else {
                cout << "\t\tRoute not found.\n";
            }
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Add bus
   

void addBus() {
    string busNumber, routeName, busTiming;
    int totalSeats;
    double fare;

    // Prompt and input bus details
    cout << "\n\tEnter Bus Number: ";
    getline(cin, busNumber);  // Use getline to handle input correctly

    cout << "\tEnter Route Name: ";
    getline(cin, routeName);

    cout << "\tEnter Total Seats: ";
    cin >> totalSeats;

    // Clear input buffer to handle newline characters
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\tEnter Bus Timing (e.g., 10:30 AM): ";
    getline(cin, busTiming);

    cout << "\tEnter Fare: ";
    cin >> fare;

    // Clear input buffer to avoid issues with further inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Append data to the file and in-memory structure
    ofstream busesFile("buses.txt", ios::app);
    if (busesFile.is_open()) {
        busesFile << busNumber << "," << routeName << "," << totalSeats << "," << busTiming << "," << fare << "\n";
        busesFile.close();

        // Update the in-memory buses list
        for (const Route& route : routes) {
            if (route.getName() == routeName) {
                buses.push_back(Bus(busNumber, route, totalSeats, busTiming, fare));
                cout << "\n\tBus added successfully.\n";
                return;
            }
        }
        cout << "\n\tRoute not found. Bus not added to the system.\n";
    } else {
        cout << "\t\tUnable to open buses file.\n";
    }
}

void addBus(const string& busNumber, const string& routeName, int totalSeats, const string& busTiming, double fare) {
    // Append data to the file and in-memory structure
    ofstream busesFile("buses.txt", ios::app);
    if (busesFile.is_open()) {
        busesFile << busNumber << "," << routeName << "," << totalSeats << "," << busTiming << "," << fare << "\n";
        busesFile.close();

        // Update the in-memory buses list
        bool routeFound = false;
        for (const Route& route : routes) {
            if (route.getName() == routeName) {
                buses.push_back(Bus(busNumber, route, totalSeats, busTiming, fare));
                routeFound = true;
                cout << "\n\tBus added successfully.\n";
                break;
            }
        }
        if (!routeFound) {
            cout << "\n\tRoute not found. Bus added to the file but not linked to a valid route.\n";
        }
    } else {
        cout << "\t\tUnable to open buses file.\n";
    }
}



    
  



void updateBus(const string& busNumber, const string& newRouteName, int newTotalSeats, const string& newBusTiming, double newFare) {
    ifstream busesFile("buses.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    string line;

    if (busesFile.is_open() && tempFile.is_open()) {
        while (getline(busesFile, line)) {
            stringstream ss(line);
            string busNum, routeName, busTiming;
            int totalSeats;
            double fare;

            getline(ss, busNum, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(); // Ignore the comma
            getline(ss, busTiming, ',');
            ss >> fare;

            if (busNum == busNumber) {
                tempFile << busNum << "," << newRouteName << "," << newTotalSeats << "," << newBusTiming << "," << newFare << "\n";
                found = true;

                // Update the vector storing buses
                for (Bus& bus : buses) {
                    if (bus.getBusNumber() == busNumber) {
                        for (const Route& route : routes) {
                            if (route.getName() == newRouteName) {
                                bus = Bus(busNumber, route, newTotalSeats, newBusTiming, newFare);
                                break;
                            }
                        }
                        break;
                    }
                }
            } else {
                tempFile << line << "\n";
            }
        }
        busesFile.close();
        tempFile.close();

        // Remove the old file and rename the temp file to the original file name
        remove("buses.txt");
        rename("temp.txt", "buses.txt");

        if (found) {
            cout << "Bus information updated successfully.\n";
        } else {
            cout << "Bus number not found.\n";
        }
    } else {
        cout << "Error opening file.\n";
    }
}



    void deleteBus(const string& busNumber) {
        ifstream busesFile("buses.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        string line;

        if (busesFile.is_open() && tempFile.is_open()) {
            while (getline(busesFile, line)) {
                stringstream ss(line);
                string busNum, routeName;
                int totalSeats;
                getline(ss, busNum, ',');
                getline(ss, routeName, ',');
                ss >> totalSeats;

                if (busNum == busNumber) {
                    found = true;
                    buses.erase(remove_if(buses.begin(), buses.end(), [&](const Bus& bus) {
                        return bus.getBusNumber() == busNumber;
                    }), buses.end());
                } else {
                    tempFile << line << "\n";
                }
            }
            busesFile.close();
            tempFile.close();
            remove("buses.txt");
            rename("temp.txt", "buses.txt");

            if (found) {
                cout << "\t\tBus deleted successfully.\n";
            } else {
                cout << "\t\tBus not found.\n";
            }
        } else {
            cout << "\t\tUnable to open buses file.\n";
        }
    }
};










// Define the BusReservationSystem class with necessary member functions
class BusReservationSystem {
public:
    BusReservationSystem() {
        // Load routes from file
        ifstream routesFile("routes.txt");
        if (routesFile.is_open()) {
            string line;
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string name, source, destination;
                int distance;
                getline(ss, name, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;
                routes.push_back(Route(name, source, destination, distance));
            }
            routesFile.close();
        }

        

   ifstream busesFile("buses.txt");
    if (busesFile.is_open()) {
        string line;
        while (getline(busesFile, line)) {
            stringstream ss(line);
            string busNumber, routeName, busTiming;
            int totalSeats;
            double fare;

            getline(ss, busNumber, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(); // Ignore the comma
            getline(ss, busTiming, ',');
            ss >> fare;

            for (const Route& route : routes) {
                if (route.getName() == routeName) {
                    buses.push_back(Bus(busNumber, route, totalSeats, busTiming, fare));
                    break;
                }
            }
        }
        busesFile.close();
    }
}

    void registerUser(const string& username, const string& password) {
        users.push_back(User(username, password));
        cout << "\n\t\tUser registered successfully. Please login to continue!\n";
    }

    bool authenticateUser(const string& username, const string& password) {
        for (const User& user : users) {
            string lowercaseUsername = user.getUsername();
            string lowercaseInputUsername = username;
            transform(lowercaseUsername.begin(), lowercaseUsername.end(), lowercaseUsername.begin(), ::tolower);
            transform(lowercaseInputUsername.begin(), lowercaseInputUsername.end(), lowercaseInputUsername.begin(), ::tolower);

            if (lowercaseUsername == lowercaseInputUsername && user.getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    string getPassword() {
        string password;
        char ch;
        while (true) {
            ch = _getch(); 
            if (ch == '\r') { 
                cout << endl;
                break;
            } else if (ch == '\b' && !password.empty()) { 
                password.pop_back();
                cout << "\b \b";
            } else if (ch != '\b') {
                password += ch;
                cout << '*'; 
            }
        }
        return password;
    }

    // Function to change password
void changePassword(const string& username) {
    cout << "\n\t\t\tEnter new password: ";
    string newPassword = getPassword();
    string filename = "user_credentials.txt";
    ifstream file(filename);
    vector<string> lines;
    bool found = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                if (storedUsername == username) {
                    line = storedUsername + "," + newPassword;
                    found = true;
                }
            }
            lines.push_back(line);
        }
        file.close();
    }

    if (found) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const string& line : lines) {
                outFile << line << endl;
            }
            outFile.close();
            cout << "\n\t\tPassword changed successfully!\n";
        } else {
            cout << "\n\t\tUnable to open credentials file for writing.\n";
        }
    } else {
        cout << "\n\t\tUsername not found.\n";
    }
}



// Function to change admin password
void changeAdminPassword(const string& adminUsername) {
    cout << "\n\t\t\tEnter new password: ";
    string newPassword = getPassword();
    string filename = "admin_credentials.txt";
    ifstream file(filename);
    vector<string> lines;
    bool found = false;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string storedUsername = line.substr(0, commaPos);
                if (storedUsername == adminUsername) {
                    line = storedUsername + "," + newPassword;
                    found = true;
                }
            }
            lines.push_back(line);
        }
        file.close();
    }

    if (found) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (const string& line : lines) {
                outFile << line << endl;
            }
            outFile.close();
            cout << "\n\t\tPassword changed successfully!\n";
        } else {
            cout << "\n\t\tUnable to open credentials file for writing.\n";
        }
    } else {
        cout << "\n\t\tAdmin username not found.\n";
    }
}

    User& findUser(const string& username) {
        for (User& user : users) {
            if (user.getUsername() == username) {
                return user;
            }
        }
        throw runtime_error("User not found");
    }

    /*void displayRoutes() const {
        cout << "\n\t\t------ Available Routes ------\n";
        for (const Route& route : routes) {
            cout << "\n\t\tRoute Name: " << route.getName() << " (" << route.getSource() << " to " << route.getDestination() << ")\n";
            cout << "\t\t\tDistance: " << route.getDistance() << " km" << endl;
        }
    }*/

   void displayRoutes() {
    string source, destination;
    set<string> locations; // Set to store unique locations

    // Populate the locations set
    for (const auto& route : routes) {
        string source = route.getSource();
        source.erase(0, source.find_first_not_of(" \t")); // Trim leading spaces
        source.erase(source.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(source);

        string destination = route.getDestination();
        destination.erase(0, destination.find_first_not_of(" \t")); // Trim leading spaces
        destination.erase(destination.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(destination);
    }

    cout << "\n\t-----------  Routes List  ------------\n";
    ifstream routesFile("routes.txt");
    string line;
    if (routesFile.is_open()) {
        while (getline(routesFile, line)) {
            stringstream ss(line);
            string name, source, destination;
            int distance;
            getline(ss, name, ',');
            getline(ss, source, ',');
            getline(ss, destination, ',');
            ss >> distance;

            cout << "\tRoute Name: " << name << "\n";
            cout << "\tSource: " << source << "\n";
            cout << "\tDestination: " << destination << "\n";
            cout << "\tDistance: " << distance << " km\n";
            cout << "\t--------------------------------------\n";
        }
        routesFile.close();
    } else {
        cout << "\t\tUnable to open routes file.\n";
    }

    // New functionality to display available locations and routes
    cout << "\n\tAvailable Locations:\n";
    for (const string& location : locations) {
        cout << "\t- " << location << "\n";
    }

    cout << "\n\tEnter Source: ";
    cin.ignore();
    getline(cin, source);
    cout << "\tEnter Destination: ";
    getline(cin, destination);

    vector<int> matchingRoutes;
    cout << "\n\tAvailable Routes:\n";
    for (size_t i = 0; i < routes.size(); ++i) {
        if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
            cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
            matchingRoutes.push_back(i);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "\n\tNo routes available for the entered source and destination.\n";
        return;
    }

    string selectedRouteName;
    cout << "\n\tSelect a Route (Enter the Route Name): ";
    getline(cin, selectedRouteName);

    int selectedRoute = -1;
    for (size_t i = 0; i < matchingRoutes.size(); ++i) {
        if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
            selectedRoute = matchingRoutes[i];
            break;
        }
    }

    if (selectedRoute == -1) {
        cout << "\n\tInvalid route name. Please try again.\n";
        return;
    }

    vector<int> matchingBuses;
    cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < buses.size(); ++i) {
        if (buses[i].getRoute().getName() == routes[selectedRoute].getName()) {
            cout << "\t" << i + 1 << ". Bus Number: " << buses[i].getBusNumber() << "\n";
            matchingBuses.push_back(i);
        }
    }

    if (matchingBuses.empty()) {
        cout << "\n\tNo buses available for the selected route.\n";
        return;
    }
}

    

   void displayBuses() const {
    cout << "\n\t-----------  Buses List  ------------\n";
    ifstream busesFile("buses.txt");
    string line;

    if (busesFile.is_open()) {
        while (getline(busesFile, line)) {
            stringstream ss(line);
            string busNumber, routeName, busTiming;
            int totalSeats;
            double fare;

            // Parse the line
            getline(ss, busNumber, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(); // Ignore the comma
            getline(ss, busTiming, ',');
            ss >> fare;

            // Display the parsed information
            cout << "\tBus Number: " << busNumber << "\n";
            cout << "\tRoute Name: " << routeName << "\n";
            cout << "\tTotal Seats: " << totalSeats << "\n";
            cout << "\tBus Timing: " << busTiming << "\n";
            cout << "\tFare: " << fare << "\n";
            cout << "\t------------------------------------\n";
        }
        busesFile.close();
    } else {
        cout << "\t\tUnable to open buses file.\n";
    }
}


    void displayBusesForRoute(int selectedRoute) const {
        cout << "\t\t\tBuses available for Route " << routes[selectedRoute - 1].getName() << ":\n";
        for (const Bus& bus : buses) {
            if (bus.getRoute().getName() == routes[selectedRoute - 1].getName()) {
                bus.displayBusInfo();
                cout << endl;
            }
        }
    }


void bookTicket(const string& username) {


    string source, destination;
    int numberOfTickets;

 
    set<string> locations;
    for (const auto& route : routes) {
        string routeSource = route.getSource();
        routeSource.erase(0, routeSource.find_first_not_of(" \t"));
        routeSource.erase(routeSource.find_last_not_of(" \t") + 1);
        locations.insert(routeSource);

        string routeDestination = route.getDestination();
        routeDestination.erase(0, routeDestination.find_first_not_of(" \t"));
        routeDestination.erase(routeDestination.find_last_not_of(" \t") + 1);
        locations.insert(routeDestination);
    }

    cout << "\n\tAvailable Locations:\n";
    for (const string& location : locations) {
        cout << "\t- " << location << "\n";
    }

    cout << "\n\tEnter Source: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear previous input
    getline(cin, source);
    cout << "\tEnter Destination: ";
    getline(cin, destination);

    vector<int> matchingRoutes;
    cout << "\n\tAvailable Routes:\n";
    for (size_t i = 0; i < routes.size(); ++i) {
        if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
            cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
            matchingRoutes.push_back(i);
        }
    }

    if (matchingRoutes.empty()) {
        cout << "\n\tNo routes available for the entered source and destination.\n";
        return;
    }

    string selectedRouteName;
    cout << "\n\tSelect a Route (Enter the Route Name): ";
    getline(cin, selectedRouteName);

    int selectedRoute = -1;
    for (size_t i = 0; i < matchingRoutes.size(); ++i) {
        if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
            selectedRoute = matchingRoutes[i];
            break;
        }
    }

    if (selectedRoute == -1) {
        cout << "\n\tInvalid route name. Please try again.\n";
        return;
    }

    vector<int> matchingBuses;
    cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < buses.size(); ++i) {
        if (buses[i].getRoute().getName() == routes[selectedRoute].getName()) {
            matchingBuses.push_back(i);
        }
    }

    if (matchingBuses.empty()) {
        cout << "\n\tNo buses available for the selected route.\n";
        return;
    }

    cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
    for (size_t i = 0; i < matchingBuses.size(); ++i) {
        cout << "\t" << i + 1 << ". Bus Number: " << buses[matchingBuses[i]].getBusNumber()
             << " | Timing: " << buses[matchingBuses[i]].getBusTiming()
             << " | Fare: ₹" << buses[matchingBuses[i]].getFare() << "\n";
    }

    char sortOptionChoice;
    cout << "\n\tDo you want to sort the buses? (y/n): ";
    cin >> sortOptionChoice;

    if (sortOptionChoice == 'y' || sortOptionChoice == 'Y') {
        int sortOption;
        bool exitSorting = false;  // Flag to manage sorting loop

        // Keep asking the user for sorting until they choose to exit
        while (!exitSorting) {
            cout << "\n\tSort Buses By:\n";
            cout << "\t1. Time\n";
            cout << "\t2. Fare\n";
            cout << "\t3. Exit Sorting\n";
            cout << "\tEnter your choice: ";
            cin >> sortOption;

            switch (sortOption) {
                case 1: {
                    // Sorting by bus timing (converted to minutes for proper comparison)
                    sort(matchingBuses.begin(), matchingBuses.end(), [this](int a, int b) {
                        return convertTimeToMinutes(buses[a].getBusTiming()) < convertTimeToMinutes(buses[b].getBusTiming());
                    });
                    cout << "\nBuses sorted by Time.\n";
                    break;
                }
                case 2: {
                    // Sorting by fare
                    sort(matchingBuses.begin(), matchingBuses.end(), [this](int a, int b) {
                        return buses[a].getFare() < buses[b].getFare();
                    });
                    cout << "\nBuses sorted by Fare.\n";
                    break;
                }
                case 3:
                    cout << "\nExiting sorting...\n";
                    exitSorting = true;  // Exit sorting loop, but not the booking function
                    break;
                default:
                    cout << "\nInvalid choice! Try again.\n";
                    continue; // Continue to the next iteration if the choice is invalid
            }

            // Display the sorted buses after each sort operation
            if (!exitSorting) {
                cout << "\nSorted Buses:\n";
                for (size_t i = 0; i < matchingBuses.size(); ++i) {
                    cout << "\t" << i + 1 << ". Bus Number: " << buses[matchingBuses[i]].getBusNumber()
                         << " | Timing: " << buses[matchingBuses[i]].getBusTiming()
                         << " | Fare: ₹" << buses[matchingBuses[i]].getFare() << "\n";
                }
            }
        }
    } else {
        cout << "\nSorting skipped.\n";
    }
    

    // Select bus
    string selectedBusString;
    cout << "\n\tSelect a Bus (Enter the Bus Number): ";
    cin.ignore();
    getline(cin, selectedBusString);

    int selectedBusIndex = -1;
    for (size_t i = 0; i < matchingBuses.size(); ++i) {
        if (buses[matchingBuses[i]].getBusNumber() == selectedBusString) {
            selectedBusIndex = matchingBuses[i];
            break;
        }
    }

    if (selectedBusIndex == -1) {
        cout << "\n\tInvalid bus number. Please try again.\n";
        return;
    }

    buses[selectedBusIndex].displayAvailableSeats();

    cout << "\n\tEnter the number of tickets you want to book: ";
    cin >> numberOfTickets;

    if (cin.fail() || numberOfTickets < 1 || numberOfTickets > buses[selectedBusIndex].getTotalSeats()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\tInvalid number of tickets. Please try again.\n";
        return;
    }

    vector<pair<string, int>> travelers;
    for (int i = 1; i <= numberOfTickets; ++i) {
        string travelerName;
        int travelerAge;
        cout << "\n\tEnter Traveler " << i << "'s Name: ";
        cin.ignore();
        getline(cin, travelerName);
        cout << "\tEnter Traveler " << i << "'s Age: ";
        cin >> travelerAge;

        travelers.push_back({travelerName, travelerAge});
    }

    vector<Ticket> userTickets;
    for (int i = 0; i < numberOfTickets; ++i) {
        int selectedSeat;
        cout << "\n\tEnter Seat Number for Traveler " << (i + 1) << ": ";
        cin >> selectedSeat;

        if (cin.fail() || selectedSeat < 1 || selectedSeat > buses[selectedBusIndex].getTotalSeats() ||
            !buses[selectedBusIndex].reserveSeat(selectedSeat)) {
            cout << "\n\tInvalid or unavailable seat number. Booking failed for Traveler " << (i + 1) << ".\n";
            continue;
        }

        Ticket ticket(travelers[i].first, selectedSeat, routes[selectedRoute], buses[selectedBusIndex]);
        userTickets.push_back(ticket);

        cout << "\n\t\t\tTicket for Traveler " << (i + 1) << ":\n";
        cout << "\t\t\tPassenger: " << ticket.getPassengerName() << " (Age: " << travelers[i].second << ")\n";
        cout << "\t\t\tBus Number: " << buses[selectedBusIndex].getBusNumber() << "\n";
        cout << "\t\t\tRoute: " << ticket.getRoute().getName() << " (" << ticket.getRoute().getSource() << " to "
             << ticket.getRoute().getDestination() << ")\n";
        cout << "\t\t\tSeat Number: " << ticket.getSeatNumber() << "\n";
    }

   

    ofstream ticketsFile("tickets.txt", ios::app);
    if (ticketsFile.is_open()) {
        for (const auto& ticket : userTickets) {
            ticketsFile << username << "," << ticket.getPassengerName() << "," << ticket.getSeatNumber() << ","
                        << ticket.getRoute().getName() << "," << ticket.getBus().getBusNumber() << "\n";
        }
        ticketsFile.close();
    }

    

    printUserTickets(username);
}

int convertTimeToMinutes(const string& timeStr) {
    int hours = stoi(timeStr.substr(0, 2));
    int minutes = stoi(timeStr.substr(3, 2));
    return (hours * 60) + minutes;
}





void printUserTickets(const string& username) {
    cout << "\n\tTickets for User: " << username << "\n";
    ifstream ticketsFile("tickets.txt");
    string line;
    while (getline(ticketsFile, line)) {
        stringstream ss(line);
        string storedUsername, passengerName, seatNumber, routeName, busNumber;
        
        // Extract ticket details from the file
        getline(ss, storedUsername, ',');
        getline(ss, passengerName, ',');
        getline(ss, seatNumber, ',');
        getline(ss, routeName, ',');
        getline(ss, busNumber, ',');
        
        // Check if the ticket belongs to the logged-in user
        if (storedUsername == username) {
            cout << "\n\t\t------ Ticket ------" << endl;
            cout << "\t\tPassenger: " << passengerName << endl;
            cout << "\t\tSeat Number: " << seatNumber << endl;
            cout << "\t\tRoute: " << routeName << endl;
            cout << "\t\tBus Number: " << busNumber << endl;
        }
    }
    ticketsFile.close();
}





void cancelTicket(const string& username) {
    ifstream ticketsFile("tickets.txt");
    if (!ticketsFile.is_open()) {
        cout << "\n\tError: Unable to open the tickets file.\n";
        return;
    }

    // Temporary vector to store all tickets for the logged-in user
    vector<string> updatedTickets;
    string line;
    bool ticketFound = false;
    int selectedBusIndex = -1; // To store the index of the bus
    int seatNumberToRelease = -1; // To store the seat number to release
    vector<string> userTickets;  // To store the tickets for this user

    // Display the tickets for the logged-in user
    cout << "\n\tTickets for User: " << username << "\n";
    int ticketIndex = 1;
    while (getline(ticketsFile, line)) {
        stringstream ss(line);
        string storedUsername, passengerName, seatNumber, routeName, busNumber;
        
        // Extract ticket details from the file
        getline(ss, storedUsername, ',');
        getline(ss, passengerName, ',');
        getline(ss, seatNumber, ',');
        getline(ss, routeName, ',');
        getline(ss, busNumber, ',');

        // Check if the ticket belongs to the logged-in user
        if (storedUsername == username) {
            cout << "\n\t\t------ Ticket " << ticketIndex++ << " ------" << endl;
            cout << "\t\tPassenger: " << passengerName << endl;
            cout << "\t\tSeat Number: " << seatNumber << endl;
            cout << "\t\tRoute: " << routeName << endl;
            cout << "\t\tBus Number: " << busNumber << endl;

            // Store this ticket in the user's list of tickets
            userTickets.push_back(line);

            // Capture the seat number and bus number for cancellation
            seatNumberToRelease = stoi(seatNumber);  // Convert seat number to integer
            // Find the bus index by matching bus number
            for (size_t i = 0; i < buses.size(); ++i) {
                if (buses[i].getBusNumber() == busNumber) {
                    selectedBusIndex = i;
                    break;
                }
            }
        } else {
            // If it's not the current user's ticket, add it to the updatedTickets list
            updatedTickets.push_back(line);
        }
    }
    ticketsFile.close();

    if (userTickets.empty()) {
        cout << "\n\tNo tickets found for user: " << username << "\n";
        return;
    }

    // Ask the user which ticket to cancel
    int ticketToCancel;
    cout << "\n\tEnter the ticket number to cancel: ";
    cin >> ticketToCancel;

    if (ticketToCancel < 1 || ticketToCancel > userTickets.size()) {
        cout << "\n\tInvalid ticket number.\n";
        return;
    }

    // Remove the selected ticket from the user's list
    userTickets.erase(userTickets.begin() + ticketToCancel - 1);

    // Reopen the file and write the updated tickets for all users, excluding the canceled ticket
    ofstream outFile("tickets.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "\n\tError: Unable to save updated tickets.\n";
        return;
    }

    // Write back the updated tickets for all users (excluding the canceled ticket)
    for (const string& ticket : updatedTickets) {
        outFile << ticket << "\n";
    }

    // Write back the remaining tickets for the current user
    for (const string& ticket : userTickets) {
        outFile << ticket << "\n";
    }

    outFile.close();

    // Debugging: Check if the file has been written correctly
    cout << "\n\tTickets file updated successfully. Releasing seat: " << seatNumberToRelease << "\n";

    // Update the seat availability on the bus
    if (selectedBusIndex != -1) {
        // Update the seats_status file after canceling the ticket
        updateSeatStatus(selectedBusIndex, seatNumberToRelease);
        cout << "\n\tSeat number " << seatNumberToRelease << " is now available.\n";
    }

    cout << "\n\tTicket successfully canceled.\n";
}

// Function to update seat availability in the seats_status file
void updateSeatStatus(int busIndex, int seatNumberToRelease) {
    ifstream seatsFile("seats_status.txt");
    if (!seatsFile.is_open()) {
        cout << "\n\tError: Unable to open the seats_status file.\n";
        return;
    }

    vector<string> seatStatuses;
    string line;

    // Read the seat statuses for all buses
    while (getline(seatsFile, line)) {
        stringstream ss(line);
        string busNumber, seatStatus;
        getline(ss, busNumber, ',');
        getline(ss, seatStatus, ',');

        // If we find the bus matching the selected one, update the seat status
        if (busNumber == buses[busIndex].getBusNumber()) {
            // Check if this is the seat we need to release
            if (stoi(seatStatus) == seatNumberToRelease) {
                seatStatus = "available"; // Mark the seat as available
            }
        }

        // Add the updated or unchanged status to the list
        seatStatuses.push_back(busNumber + "," + seatStatus);
    }
    seatsFile.close();

    // Write back the updated seat statuses to the file
    ofstream outFile("seats_status.txt", ios::trunc);
    if (!outFile.is_open()) {
        cout << "\n\tError: Unable to save updated seat statuses.\n";
        return;
    }

    for (const string& status : seatStatuses) {
        outFile << status << "\n";
    }

    outFile.close();
}








void run() {
    while (true) {
        cout << "\n\t------ Welcome to the Bus Reservation System ------\n\n";
        cout << "\t\t\t1. Register\n\t\t\t2. Log In\n\t\t\t3. Register Admin\n\t\t\t4. Log In Admin\n\t\t\t5. Exit\n";
        cout << "\n\t\t\tEnter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Inline registerUser functionality
            string username, password;
            cout << "\n\t\t\tEnter username: ";
            cin >> username;
            cout << "\t\t\tEnter password: ";
            password = getPassword();

            string filename = "user_credentials.txt";
            ofstream file(filename, ios::app);
            if (file.is_open()) {
                file << username << "," << password << "\n";
                file.close();
                cout << "\n\t\tUser registered successfully!\n";
            } else {
                cout << "\n\t\tError: Unable to open file for registration.\n";
            }
        } else if (choice == 2) {
            // Inline authenticateUser functionality
            string username, password;
            cout << "\n\t\t\tEnter username: ";
            cin >> username;
            cout << "\t\t\tEnter password: ";
            password = getPassword();

            string filename = "user_credentials.txt";
            ifstream file(filename);
            bool authenticated = false;

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    size_t commaPos = line.find(',');
                    if (commaPos != string::npos) {
                        string storedUsername = line.substr(0, commaPos);
                        string storedPassword = line.substr(commaPos + 1);
                        if (storedUsername == username && storedPassword == password) {
                            authenticated = true;
                            break;
                        }
                    }
                }
                file.close();
            }

                 if (authenticated) {
                cout << "\n\t\t\tLogged in successfully!\n";
                userMenu(username);
            } else {
                cout << "\n\t\tAuthentication failed! Please check your username and password.\n";
                char choice;
                cout << "\n\t\tWould you like to change your password? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    cout << "\n\t\tPlease verify your username to change the password.\n";
                    cout << "\t\t\tEnter username: ";
                    cin >> username;
                    changePassword(username);
                }
            }
        }
       
       
       
       
        else if (choice == 3) {
            // Inline registerUser functionality for admin
            string adminUsername, adminPassword;
            cout << "\n\t\t\tEnter new admin username: ";
            cin >> adminUsername;
            cout << "\t\t\tEnter new admin password: ";
            adminPassword = getPassword();

            string filename = "admin_credentials.txt";
            ofstream file(filename, ios::app);
            if (file.is_open()) {
                file << adminUsername << "," << adminPassword << "\n";
                file.close();
                cout << "\n\t\tAdmin registered successfully!\n";
            } else {
                cout << "\n\t\tError: Unable to open file for registration.\n";
            }
        } else if (choice == 4) {
            // Inline authenticateUser functionality for admin
            string adminUsername, adminPassword;
            cout << "\n\t\t\tEnter admin username: ";
            cin >> adminUsername;
            cout << "\t\t\tEnter admin password: ";
            adminPassword = getPassword();

            string filename = "admin_credentials.txt";
            ifstream file(filename);
            bool authenticated = false;

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    size_t commaPos = line.find(',');
                    if (commaPos != string::npos) {
                        string storedUsername = line.substr(0, commaPos);
                        string storedPassword = line.substr(commaPos + 1);
                        if (storedUsername == adminUsername && storedPassword == adminPassword) {
                            authenticated = true;
                            break;
                        }
                    }
                }
                file.close();
            }

           
         if (authenticated) {
                cout << "\n\t\t\tAdmin logged in successfully!\n";
                 adminMenu(); // Uncomment and implement adminMenu function as needed
            } else {
                cout << "\n\t\tAuthentication failed! Please check your admin username and password.\n";
                char choice;
                cout << "\n\t\tWould you like to change your password? (y/n): ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    cout << "\n\t\tPlease verify your admin username to change the password.\n";
                    cout << "\t\t\tEnter admin username: ";
                    cin >> adminUsername;
                    changeAdminPassword(adminUsername);
                }
            }
        }
       
       
        else if (choice == 5) {
            cout << "\n\t\tExiting the Bus Reservation System. Goodbye!\n";
            break;
        } else {
            cout << "\n\t\tInvalid choice! Please try again.\n";
        }
    }
}




    void userMenu(const string& username) {
        int choice = 0;
        while (true) {
            cout << "\n\t-----------  Welcome to the User Menu  ------------\n\n";
            cout << "\t\t\t1. Display Routes\n\t\t\t2. Display Buses\n\t\t\t3. Book Ticket\n\t\t\t4. Cancel Ticket\n\t\t\t5. Logout\n";
            cout << "\n\t\t\tEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                displayRoutes();
            } else if (choice == 2) {
                displayBuses();
            } else if (choice == 3) {
                bookTicket(username);
            } else if (choice == 4) {
                cancelTicket(username);
            } else if (choice == 5) {
                cout << "\n\t\t\tLogged out successfully.\n";
                break;
            }
        }
    }

    private:
    vector<User> users;
    vector<Route> routes;
    vector<Bus> buses;


   
   
   void adminMenu() {
    int choice = 0;
    while (true) {
        cout << "\n\t-----------  Welcome to the Admin Menu  ------------\n\n";
        cout << "\t\t\t1. Add Route\n\t\t\t2. Update Route\n\t\t\t3. Delete Route\n";
        cout << "\t\t\t4. Add Bus\n\t\t\t5. Update Bus\n\t\t\t6. Delete Bus\n";
        cout << "\t\t\t7. Display Routes\n\t\t\t8. Display Buses\n\t\t\t9. Logout\n";
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, source, destination;
                int distance;
                cout << "\n\t\tEnter Route Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "\t\tEnter Route Source: ";
                getline(cin, source);
                cout << "\t\tEnter Route Destination: ";
                getline(cin, destination);
                cout << "\t\tEnter Route Distance: ";
                cin >> distance;
                addRoute(name, source, destination, distance);
                break;
            }
            case 2: {
                string name, newSource, newDestination;
                int newDistance;
                cout << "\n\t\tEnter Route Name to Update: ";
                cin.ignore();
                getline(cin, name);
                cout << "\t\tEnter New Route Source: ";
                getline(cin, newSource);
                cout << "\t\tEnter New Route Destination: ";
                getline(cin, newDestination);
                cout << "\t\tEnter New Route Distance: ";
                cin >> newDistance;
                updateRoute(name, newSource, newDestination, newDistance);
                break;
            }
            case 3: {
                string name;
                cout << "\n\t\tEnter Route Name to Delete: ";
                cin.ignore();
                getline(cin, name);
                deleteRoute(name);
                break;
            }
            case 4: {
              string busNumber, routeName, busTiming;
double fare;
int totalSeats;

cout << "\n\t\tEnter Bus Number: ";
cin.ignore(); // Clear any leftover newline characters from previous inputs
getline(cin, busNumber);

cout << "\t\tEnter Route Name: ";
getline(cin, routeName);

cout << "\t\tEnter Total Seats: ";
cin >> totalSeats;

// Clear input buffer to handle subsequent getline input
cin.ignore(numeric_limits<streamsize>::max(), '\n');

cout << "\t\tEnter Bus Timing (e.g., 10:30 AM): ";
getline(cin, busTiming);

cout << "\t\tEnter Fare in rs: ";
cin >> fare;

// Clear input buffer for any further inputs
cin.ignore(numeric_limits<streamsize>::max(), '\n');

// Call addBus with all collected inputs
addBus(busNumber, routeName, totalSeats, busTiming, fare);
break;

            }
            case 5: {
                

                 string busNumber, newRouteName, newBusTiming;
    int newTotalSeats;
    double newFare;

    cout << "\n\t\tEnter Bus Number to Update: ";
    cin.ignore(); // Clear any leftover newline characters
    getline(cin, busNumber);

    cout << "\t\tEnter New Route Name: ";
    getline(cin, newRouteName);

    cout << "\t\tEnter New Total Seats: ";
    cin >> newTotalSeats;

    // Clear input buffer to handle subsequent getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\t\tEnter New Bus Timing (e.g., 10:30 AM): ";
    getline(cin, newBusTiming);

    cout << "\t\tEnter New Fare in rs: ";
    cin >> newFare;

    // Call the updateBus function with collected inputs
    updateBus(busNumber, newRouteName, newTotalSeats, newBusTiming, newFare);
    break;
            }
            case 6: {
                string busNumber;
                cout << "\n\t\tEnter Bus Number to Delete: ";
                cin.ignore();
                getline(cin, busNumber);
                deleteBus(busNumber);
                break;
            }
            case 7: {

                string source, destination;
    int numberOfTickets;

    set<string> locations; // Set to store unique locations
    for (const auto& route : routes) {
        string source = route.getSource();
        source.erase(0, source.find_first_not_of(" \t")); // Trim leading spaces
        source.erase(source.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(source);

        string destination = route.getDestination();
        destination.erase(0, destination.find_first_not_of(" \t")); // Trim leading spaces
        destination.erase(destination.find_last_not_of(" \t") + 1); // Trim trailing spaces
        locations.insert(destination);
    }
                
                cout << "\n\t-----------  Routes List  ------------\n";
                ifstream routesFile("routes.txt");
                string line;
                if (routesFile.is_open()) {
                    while (getline(routesFile, line)) {
                        stringstream ss(line);
                        string name, source, destination;
                        int distance;
                        getline(ss, name, ',');
                        getline(ss, source, ',');
                        getline(ss, destination, ',');
                        ss >> distance;

                        cout << "\tRoute Name: " << name << "\n";
                        cout << "\tSource: " << source << "\n";
                        cout << "\tDestination: " << destination << "\n";
                        cout << "\tDistance: " << distance << " km\n";
                        cout << "\t--------------------------------------\n";
                    }
                    routesFile.close();
                } else {
                    cout << "\t\tUnable to open routes file.\n";
                }

                // New functionality to display available locations and routes
                cout << "\n\tAvailable Locations:\n";
                for (const string& location : locations) {
                    cout << "\t- " << location << "\n";
                }

                cout << "\n\tEnter Source: ";
                cin.ignore();
                getline(cin, source);
                cout << "\tEnter Destination: ";
                getline(cin, destination);

                vector<int> matchingRoutes;
                cout << "\n\tAvailable Routes:\n";
                for (size_t i = 0; i < routes.size(); ++i) {
                    if (routes[i].getSource() == source && routes[i].getDestination() == destination) {
                        cout << "\t" << i + 1 << ". " << routes[i].getName() << " (" << source << " to " << destination << ")\n";
                        matchingRoutes.push_back(i);
                    }
                }

                if (matchingRoutes.empty()) {
                    cout << "\n\tNo routes available for the entered source and destination.\n";
                    break;
                }

                string selectedRouteName;
                cout << "\n\tSelect a Route (Enter the Route Name): ";
                getline(cin, selectedRouteName);

                int selectedRoute = -1;
                for (size_t i = 0; i < matchingRoutes.size(); ++i) {
                    if (routes[matchingRoutes[i]].getName() == selectedRouteName) {
                        selectedRoute = matchingRoutes[i];
                        break;
                    }
                }

                if (selectedRoute == -1) {
                    cout << "\n\tInvalid route name. Please try again.\n";
                    break;
                }

                vector<int> matchingBuses;
                cout << "\n\tAvailable Buses for Route: " << routes[selectedRoute].getName() << "\n";
                for (size_t i = 0; i < buses.size(); ++i) {
                    if (buses[i].getRoute().getName() == routes[selectedRoute].getName()) {
                        cout << "\t" << i + 1 << ". Bus Number: " << buses[i].getBusNumber() << "\n";
                        matchingBuses.push_back(i);
                    }
                }

                if (matchingBuses.empty()) {
                    cout << "\n\tNo buses available for the selected route.\n";
                    break;
                }

                break;
                
                
             
            }
            case 8: {
                cout << "\n\t-----------  Buses List  ------------\n";
                ifstream busesFile("buses.txt");
                string line;
                if (busesFile.is_open()) {
                    while (getline(busesFile, line)) {
                        stringstream ss(line);
                        string busNumber, routeName;
                        int totalSeats;
                        getline(ss, busNumber, ',');
                        getline(ss, routeName, ',');
                        ss >> totalSeats;

                        cout << "\tBus Number: " << busNumber << "\n";
                        cout << "\tRoute Name: " << routeName << "\n";
                        cout << "\tTotal Seats: " << totalSeats << "\n";
                        cout << "\t------------------------------------\n";
                    }
                    busesFile.close();
                } else {
                    cout << "\t\tUnable to open buses file.\n";
                }
                break;
            }
            case 9: {
                cout << "\n\t\t\tLogged out successfully.\n";
                return; // Exit the menu
            }
            default:
                cout << "\n\t\tInvalid choice! Please try again.\n";
        }
    }
}


  
    void addRoute(const string& name, const string& source, const string& destination, int distance) {
        ofstream routesFile("routes.txt", ios::app);
        if (routesFile.is_open()) {
            routesFile << name << "," << source << "," << destination << "," << distance << "\n";
            routes.push_back(Route(name, source, destination, distance));
            routesFile.close();
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Update route
    void updateRoute(const string& name, const string& newSource, const string& newDestination, int newDistance) {
        ifstream routesFile("routes.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        string line;

        if (routesFile.is_open() && tempFile.is_open()) {
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string routeName, source, destination;
                int distance;
                getline(ss, routeName, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;

                if (routeName == name) {
                    tempFile << routeName << "," << newSource << "," << newDestination << "," << newDistance << "\n";
                    found = true;
                    for (Route& route : routes) {
                        if (route.getName() == name) {
                            route = Route(name, newSource, newDestination, newDistance);
                            break;
                        }
                    }
                } else {
                    tempFile << line << "\n";
                }
            }
            routesFile.close();
            tempFile.close();
            remove("routes.txt");
            rename("temp.txt", "routes.txt");

            if (found) {
                cout << "\t\tRoute updated successfully.\n";
            } else {
                cout << "\t\tRoute not found.\n";
            }
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Delete route
    void deleteRoute(const string& name) {
        ifstream routesFile("routes.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        string line;

        if (routesFile.is_open() && tempFile.is_open()) {
            while (getline(routesFile, line)) {
                stringstream ss(line);
                string routeName, source, destination;
                int distance;
                getline(ss, routeName, ',');
                getline(ss, source, ',');
                getline(ss, destination, ',');
                ss >> distance;

                if (routeName == name) {
                    found = true;
                    routes.erase(remove_if(routes.begin(), routes.end(), [&](const Route& route) {
                        return route.getName() == name;
                    }), routes.end());
                } else {
                    tempFile << line << "\n";
                }
            }
            routesFile.close();
            tempFile.close();
            remove("routes.txt");
            rename("temp.txt", "routes.txt");

            if (found) {
                cout << "\t\tRoute deleted successfully.\n";
            } else {
                cout << "\t\tRoute not found.\n";
            }
        } else {
            cout << "\t\tUnable to open routes file.\n";
        }
    }

    // Add bus
   

void addBus() {
    string busNumber, routeName, busTiming;
    int totalSeats;
    double fare;

    // Prompt and input bus details
    cout << "\n\tEnter Bus Number: ";
    getline(cin, busNumber);  // Use getline to handle input correctly

    cout << "\tEnter Route Name: ";
    getline(cin, routeName);

    cout << "\tEnter Total Seats: ";
    cin >> totalSeats;

    // Clear input buffer to handle newline characters
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\tEnter Bus Timing (e.g., 10:30 AM): ";
    getline(cin, busTiming);

    cout << "\tEnter Fare: ";
    cin >> fare;

    // Clear input buffer to avoid issues with further inputs
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Append data to the file and in-memory structure
    ofstream busesFile("buses.txt", ios::app);
    if (busesFile.is_open()) {
        busesFile << busNumber << "," << routeName << "," << totalSeats << "," << busTiming << "," << fare << "\n";
        busesFile.close();

        // Update the in-memory buses list
        for (const Route& route : routes) {
            if (route.getName() == routeName) {
                buses.push_back(Bus(busNumber, route, totalSeats, busTiming, fare));
                cout << "\n\tBus added successfully.\n";
                return;
            }
        }
        cout << "\n\tRoute not found. Bus not added to the system.\n";
    } else {
        cout << "\t\tUnable to open buses file.\n";
    }
}

void addBus(const string& busNumber, const string& routeName, int totalSeats, const string& busTiming, double fare) {
    // Append data to the file and in-memory structure
    ofstream busesFile("buses.txt", ios::app);
    if (busesFile.is_open()) {
        busesFile << busNumber << "," << routeName << "," << totalSeats << "," << busTiming << "," << fare << "\n";
        busesFile.close();

        // Update the in-memory buses list
        bool routeFound = false;
        for (const Route& route : routes) {
            if (route.getName() == routeName) {
                buses.push_back(Bus(busNumber, route, totalSeats, busTiming, fare));
                routeFound = true;
                cout << "\n\tBus added successfully.\n";
                break;
            }
        }
        if (!routeFound) {
            cout << "\n\tRoute not found. Bus added to the file but not linked to a valid route.\n";
        }
    } else {
        cout << "\t\tUnable to open buses file.\n";
    }
}



    
  



void updateBus(const string& busNumber, const string& newRouteName, int newTotalSeats, const string& newBusTiming, double newFare) {
    ifstream busesFile("buses.txt");
    ofstream tempFile("temp.txt");
    bool found = false;
    string line;

    if (busesFile.is_open() && tempFile.is_open()) {
        while (getline(busesFile, line)) {
            stringstream ss(line);
            string busNum, routeName, busTiming;
            int totalSeats;
            double fare;

            getline(ss, busNum, ',');
            getline(ss, routeName, ',');
            ss >> totalSeats;
            ss.ignore(); // Ignore the comma
            getline(ss, busTiming, ',');
            ss >> fare;

            if (busNum == busNumber) {
                tempFile << busNum << "," << newRouteName << "," << newTotalSeats << "," << newBusTiming << "," << newFare << "\n";
                found = true;

                // Update the vector storing buses
                for (Bus& bus : buses) {
                    if (bus.getBusNumber() == busNumber) {
                        for (const Route& route : routes) {
                            if (route.getName() == newRouteName) {
                                bus = Bus(busNumber, route, newTotalSeats, newBusTiming, newFare);
                                break;
                            }
                        }
                        break;
                    }
                }
            } else {
                tempFile << line << "\n";
            }
        }
        busesFile.close();
        tempFile.close();

        // Remove the old file and rename the temp file to the original file name
        remove("buses.txt");
        rename("temp.txt", "buses.txt");

        if (found) {
            cout << "Bus information updated successfully.\n";
        } else {
            cout << "Bus number not found.\n";
        }
    } else {
        cout << "Error opening file.\n";
    }
}



    void deleteBus(const string& busNumber) {
        ifstream busesFile("buses.txt");
        ofstream tempFile("temp.txt");
        bool found = false;
        string line;

        if (busesFile.is_open() && tempFile.is_open()) {
            while (getline(busesFile, line)) {
                stringstream ss(line);
                string busNum, routeName;
                int totalSeats;
                getline(ss, busNum, ',');
                getline(ss, routeName, ',');
                ss >> totalSeats;

                if (busNum == busNumber) {
                    found = true;
                    buses.erase(remove_if(buses.begin(), buses.end(), [&](const Bus& bus) {
                        return bus.getBusNumber() == busNumber;
                    }), buses.end());
                } else {
                    tempFile << line << "\n";
                }
            }
            busesFile.close();
            tempFile.close();
            remove("buses.txt");
            rename("temp.txt", "buses.txt");

            if (found) {
                cout << "\t\tBus deleted successfully.\n";
            } else {
                cout << "\t\tBus not found.\n";
            }
        } else {
            cout << "\t\tUnable to open buses file.\n";
        }
    }
};

/*int main() {
    int choice;
    BusReservationSystem brs;
    TrainReservationSystem trs;

    cout << "Welcome to Belagavi Smart City Management System\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Bus Reservation System\n";
        cout << "2. Train Reservation System\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\nInvalid input. Please enter a valid choice.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nWelcome to the Bus Reservation System!\n";
                brs.run();
                break;

            case 2:
                cout << "\nWelcome to the Train Reservation System!\n";
                trs.run();
                break;

            case 3:
                cout << "\nThank you for using Belagavi Smart City Management System. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice. Please select a valid option.\n";
        }
    } while (choice != 3);

    return 0;
}*/




class MapManager {
public:
    // Constructor: Automatically load the map from the file
    MapManager() {
        loadMapFromFile();
    }

    void loadMapFromFile() {
        ifstream file("city_map.txt");
        if (!file.is_open()) {
            // If the file doesn't exist, create it
            ofstream newFile("city_map.txt");
            if (newFile.is_open()) {
                cout << "city_map.txt was not found. Created a new file.\n";
                newFile.close();
            } else {
                cerr << "Error: Unable to create city_map.txt.\n";
            }
            return;
        }

        string loc1, loc2;
        int dist, time;
        while (file >> loc1 >> loc2 >> dist >> time) {
            addaLocation(loc1, false); // Add locations silently
            addaLocation(loc2, false); // Add locations silently
            addaRoute(loc1, loc2, dist, time, false); // Add roads without redundant messages
        }
        file.close();
        cout << "City map loaded successfully from city_map.txt.\n";
    }

    // Add a location
    bool addaLocation(const string& loc, bool saveToFile = true) {
        if (adjacencyList.find(loc) == adjacencyList.end()) {
            adjacencyList[loc] = {};
            if (saveToFile) {
                cout << "Location \"" << loc << "\" added successfully.\n";
                saveMapToFile();
            }
            return true;
        } else {
            if (saveToFile) {
                cerr << "Error: Location \"" << loc << "\" already exists.\n";
            }
            return false;
        }
    }

    // Add a road between two locations
    bool addaRoute(const string& loc1, const string& loc2, int dist, int time, bool saveToFile = true) {
        if (dist <= 0 || time <= 0) {
            cerr << "Error: Distance and time must be greater than 0.\n";
            return false;
        }

        if (!locationExists(loc1) || !locationExists(loc2)) {
            cerr << "Error: One or both locations do not exist.\n";
            return false;
        }

        adjacencyList[loc1][loc2] = {dist, time};
        adjacencyList[loc2][loc1] = {dist, time};

        if (saveToFile) {
            cout << "Road between \"" << loc1 << "\" and \"" << loc2 << "\" added successfully.\n";
            saveMapToFile();
        }
        return true;
    }

    // Remove a location
    bool removeaLocation(const string& loc) {
        if (!locationExists(loc)) {
            cerr << "Error: Location \"" << loc << "\" does not exist.\n";
            return false;
        }

        adjacencyList.erase(loc);
        for (auto& pair : adjacencyList) {
            pair.second.erase(loc);
        }
        cout << "Location \"" << loc << "\" removed successfully.\n";
        saveMapToFile();
        return true;
    }

    // Remove a road between two locations
    bool removeaRoute(const string& loc1, const string& loc2) {
        if (!locationExists(loc1) || !locationExists(loc2)) {
            cerr << "Error: One or both locations do not exist.\n";
            return false;
        }

        if (adjacencyList[loc1].erase(loc2) > 0 && adjacencyList[loc2].erase(loc1) > 0) {
            cout << "Road between \"" << loc1 << "\" and \"" << loc2 << "\" removed successfully.\n";
            saveMapToFile();
            return true;
        } else {
            cerr << "Error: Road between \"" << loc1 << "\" and \"" << loc2 << "\" does not exist.\n";
            return false;
        }
    }

    // Display the city map
    void showMap() const {
        if (adjacencyList.empty()) {
            cout << "City map is empty.\n";
            return;
        }

        cout << "City Map:\n";
        for (const auto& pair : adjacencyList) {
            const string& loc = pair.first;
            const auto& neighbors = pair.second; // Adjusted type
            cout << "  " << loc << ":\n";
            for (const auto& neighbor : neighbors) {
                cout << "    -> " << neighbor.first
                     << " (Distance: " << neighbor.second.first
                     << ", Time: " << neighbor.second.second << ")\n";
            }
        }
    }

    // Check if a location exists
    bool locationExists(const string& loc) const {
        return adjacencyList.find(loc) != adjacencyList.end();
    }

    // Get neighbors of a location
    map<string, pair<int, int>> getNeighboringLocations(const string& loc) const {
        if (!locationExists(loc)) {
            cerr << "Error: Location \"" << loc << "\" does not exist.\n";
            return {};
        }
        return adjacencyList.at(loc);
    }

    // Get all locations
    vector<string> getAllLocations() const {
        vector<string> locations;
        for (const auto& pair : adjacencyList) {
            locations.push_back(pair.first);
        }
        return locations;
    }

private:
    map<string, map<string, pair<int, int>>> adjacencyList; // Updated to store distance and time

    void saveMapToFile() const {
        ofstream file("city_map.txt", ios::trunc);
        if (file.is_open()) {
            for (const auto& pair : adjacencyList) {
                const string& loc = pair.first;
                const auto& neighbors = pair.second; // Adjusted type
                for (const auto& neighbor : neighbors) {
                    if (loc < neighbor.first) { // Avoid duplicate entries
                        file << loc << " " << neighbor.first << " "
                             << neighbor.second.first << " "
                             << neighbor.second.second << "\n";
                    }
                }
            }
            file.close();
            cout << "City map saved to city_map.txt.\n";
        } else {
            cerr << "Error: Unable to save city map to city_map.txt.\n";
        }
    }
};

// Global instance of MapManager
MapManager mapManager;

// Controller Class for Admin
class AdminController {
public:
    void addaLocation() {
        string loc;
        cout << "Enter location name: ";
        cin >> loc;
        mapManager.addaLocation(loc);
    }

    void addaRoute() {
        string loc1, loc2;
        int dist, time;

        // Print all available locations
        cout << "Available locations: \n";
        for (const auto& loc : mapManager.getAllLocations()) {
            cout << loc << "\n";  // Prints each location on a new line
        }

        cout << "Enter first location: ";
        cin >> loc1;
        cout << "Enter second location: ";
        cin >> loc2;
        cout << "Enter distance: ";
        cin >> dist;
        cout << "Enter time: ";
        cin >> time;

        mapManager.addaRoute(loc1, loc2, dist, time);
    }

    void removeaLocation() {
        string loc;
        cout << "Enter location name: ";
        cin >> loc;
        mapManager.removeaLocation(loc);
    }

    

    void removeaRoute() {
        // Print all available locations
        cout << "Available locations: \n";
        for (const auto& loc : mapManager.getAllLocations()) {
            cout << loc << "\n";  // Prints each location on a new line
        }

        string loc1, loc2;
        cout << "Enter first location: ";
        cin >> loc1;
        cout << "Enter second location: ";
        cin >> loc2;
        mapManager.removeaRoute(loc1, loc2);
    }

    void viewMap() {
        mapManager.showMap();
    }
};

// Controller Class for User
class UserController {
public:
    void findOptimalPath() {
        string start, end;
        cout << "\nAvailable locations: \n";
        for (const auto& loc : mapManager.getAllLocations()) {
            cout << "-" << loc << "\n"; // Add a newline after each location
        }
        cout << "\nEnter starting location: ";
        cin >> start;
        cout << "Enter destination location: ";
        cin >> end;

        if (!mapManager.locationExists(start) || !mapManager.locationExists(end)) {
            cout << "Invalid locations.\n";
            return;
        }

        cout << "Do you want to sort the path? (y/n): ";
        char sortChoice;
        cin >> sortChoice;

        if (sortChoice == 'y' || sortChoice == 'Y') {
            cout << "Choose sorting criteria:\n";
            cout << "1. Time\n";
            cout << "2. Distance\n";
            cout << "3. Exit\n";
            int criteria;
            cin >> criteria;

            switch (criteria) {
                case 1: {
                    vector<pair<string, int>> pathWithTimes = findShortestPathByTime(start, end);
                    if (!pathWithTimes.empty()) {
                        cout << "Shortest path by time from " << start << " to " << end << ":\n";
                        int totalTime = 0;
                        for (size_t i = 0; i < pathWithTimes.size(); ++i) {
                            cout << pathWithTimes[i].first;
                            if (i > 0) {
                                cout << " (Time from previous: " << pathWithTimes[i].second << ")";
                                totalTime += pathWithTimes[i].second;
                            }
                            if (i < pathWithTimes.size() - 1) cout << " -> ";
                        }
                        cout << "\nTotal Time: " << totalTime << " units\n";
                    } else {
                        cout << "No path found from " << start << " to " << end << ".\n";
                    }
                    break;
                }
                case 2: {
                    vector<pair<string, int>> pathWithDistances = findShortestPathByDistance(start, end);
                    if (!pathWithDistances.empty()) {
                        cout << "Shortest path by distance from " << start << " to " << end << ":\n";
                        int totalDistance = 0;
                        for (size_t i = 0; i < pathWithDistances.size(); ++i) {
                            cout << pathWithDistances[i].first;
                            if (i > 0) {
                                cout << " (Distance from previous: " << pathWithDistances[i].second << ")";
                                totalDistance += pathWithDistances[i].second;
                            }
                            if (i < pathWithDistances.size() - 1) cout << " -> ";
                        }
                        cout << "\nTotal Distance: " << totalDistance << " units\n";
                    } else {
                        cout << "No path found from " << start << " to " << end << ".\n";
                    }
                    break;
                }
                case 3:
                    cout << "Exit chosen. No path displayed.\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                    break;
            }
        } else {
            // If the user doesn't want to sort, default to finding the shortest path by distance
            vector<pair<string, int>> pathWithDistances = findShortestPathByDistance(start, end);
            if (!pathWithDistances.empty()) {
                cout << "Shortest path by distance from " << start << " to " << end << ":\n";
                int totalDistance = 0;
                for (size_t i = 0; i < pathWithDistances.size(); ++i) {
                    cout << pathWithDistances[i].first;
                    if (i > 0) {
                        cout << " (Distance from previous: " << pathWithDistances[i].second << ")";
                        totalDistance += pathWithDistances[i].second;
                    }
                    if (i < pathWithDistances.size() - 1) cout << " -> ";
                }
                cout << "\nTotal Distance: " << totalDistance << " units\n";
            } else {
                cout << "No path found from " << start << " to " << end << ".\n";
            }
        }
    }

    void viewMap() {
        mapManager.showMap();
    }

private:
    vector<pair<string, int>> findShortestPathByDistance(const string& start, const string& end) {
        map<string, int> distances;
        map<string, string> previous;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        for (const auto& loc : mapManager.getAllLocations()) {
            distances[loc] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (current == end) {
                vector<pair<string, int>> pathWithDistances;
                string at = end;
                while (!at.empty()) {
                    string prev = previous[at];
                    if (!prev.empty()) {
                        int segmentDistance = mapManager.getNeighboringLocations(prev).at(at).first;
                        pathWithDistances.push_back({at, segmentDistance});
                    } else {
                        pathWithDistances.push_back({at, 0});
                    }
                    at = prev;
                }
                reverse(pathWithDistances.begin(), pathWithDistances.end());
                return pathWithDistances;
            }

            for (const auto& neighbor : mapManager.getNeighboringLocations(current)) {
                const string& neighborName = neighbor.first;
                int weight = neighbor.second.first;
                int newDist = distances[current] + weight;
                if (newDist < distances[neighborName]) {
                    distances[neighborName] = newDist;
                    previous[neighborName] = current;
                    pq.push({newDist, neighborName});
                }
            }
        }

        return {};
    }

    vector<pair<string, int>> findShortestPathByTime(const string& start, const string& end) {
        map<string, int> times;
        map<string, string> previous;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

        for (const auto& loc : mapManager.getAllLocations()) {
            times[loc] = numeric_limits<int>::max();
        }
        times[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            pq.pop();

            if (current == end) {
                vector<pair<string, int>> pathWithTimes;
                string at = end;
                while (!at.empty()) {
                    string prev = previous[at];
                    if (!prev.empty()) {
                        int segmentTime = mapManager.getNeighboringLocations(prev).at(at).second;
                        pathWithTimes.push_back({at, segmentTime});
                    } else {
                        pathWithTimes.push_back({at, 0});
                    }
                    at = prev;
                }
                reverse(pathWithTimes.begin(), pathWithTimes.end());
                return pathWithTimes;
            }

            for (const auto& neighbor : mapManager.getNeighboringLocations(current)) {
                const string& neighborName = neighbor.first;
                int weight = neighbor.second.second;
                int newTime = times[current] + weight;
                if (newTime < times[neighborName]) {
                    times[neighborName] = newTime;
                    previous[neighborName] = current;
                    pq.push({newTime, neighborName});
                }
            }
        }

        return {};
    }
};

// Application Class Definition
class TrafficManagementSystem {
public:
    void run() {
        int choice;
        do {
            cout << "\nTraffic Management System\n";
            cout << "1. Register User\n";
            cout << "2. Login User\n";
            cout << "3. Register Admin\n";
            cout << "4. Login Admin\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loginUser();
                    break;
                case 3:
                    registerAdmin();
                    break;
                case 4:
                    loginAdmin();
                    break;
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 5);
    }

private:
    void registerUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        password = getInputPassword("Enter password: ");
        
        ofstream userFile("users.txt", ios::app);
        if (userFile.is_open()) {
            userFile << username << " " << password << "\n";
            userFile.close();
            cout << "User registered successfully.\n";
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

    void loginUser() {
        string username, password, fileUsername, filePassword;
        cout << "Enter username: ";
        cin >> username;
        password = getInputPassword("Enter password: ");

        ifstream userFile("users.txt");
        if (userFile.is_open()) {
            bool found = false;
            while (userFile >> fileUsername >> filePassword) {
                if (fileUsername == username && filePassword == password) {
                    found = true;
                    break;
                }
            }
            userFile.close();

            if (found) {
                cout << "Login successful.\n";
                displayUserMenu();
            } else {
                cout << "Invalid username or password.\n";
                resetaPassword(username, "users.txt");
            }
        } else {
            cout << "Unable to open file for reading.\n";
        }
    }

    void registerAdmin() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        password = getInputPassword("Enter password: ");
        
        ofstream adminFile("admins.txt", ios::app);
        if (adminFile.is_open()) {
            adminFile << username << " " << password << "\n";
            adminFile.close();
            cout << "Admin registered successfully.\n";
        } else {
            cout << "Unable to open file for writing.\n";
        }
    }

    void loginAdmin() {
    string username, password, fileUsername, filePassword;
    cout << "Enter username: ";
    cin >> username;
    password = getInputPassword("Enter password: ");

    ifstream adminFile("admins.txt");
    if (adminFile.is_open()) {
        bool found = false;
        while (adminFile >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                found = true;
                break;
            }
        }
        adminFile.close();

        if (found) {
            cout << "Login successful.\n";
            showAdminMenu();
        } else {
            cout << "Invalid username or password.\n";
            resetaPassword(username, "admins.txt");
        }
    } else {
        cout << "Unable to open file for reading.\n";
    }
}

// Function to get input password with masking
string getInputPassword(const string& prompt) {
    cout << prompt;
    string password;
    char ch;
    while ((ch = getch()) != '\r') { // Enter key is '\r'
        if (ch == '\b' && !password.empty()) { // Backspace
            cout << "\b \b";
            password.pop_back();
        } else if (ch != '\b') {
            cout << '*';
            password.push_back(ch);
        }
    }
    cout << endl;
    return password;
}

// Function to reset admin password
void resetaPassword(const string& username, const string& filename) {
    cout << "Would you like to reset your password? (y/n): ";
    string response;
    cin >> response;
    if (response == "y") {
        string newPassword = getInputPassword("Enter new password: ");
        string tempFilename = "temp.txt";
        ifstream inFile(filename);
        ofstream tempFile(tempFilename);

        if (inFile.is_open() && tempFile.is_open()) {
            string fileUsername, filePassword;
            while (inFile >> fileUsername >> filePassword) {
                if (fileUsername == username) {
                    tempFile << fileUsername << " " << newPassword << "\n";
                } else {
                    tempFile << fileUsername << " " << filePassword << "\n";
                }
            }
            inFile.close();
            tempFile.close();
            remove(filename.c_str());
            rename(tempFilename.c_str(), filename.c_str());
            cout << "Password reset successfully.\n";
        } else {
            cout << "Unable to open file for password reset.\n";
        }
    }
}


    void displayUserMenu() {
        UserController  user;
        int choice;
        do {
            cout << "\nUser Menu:\n";
            cout << "1. Find Shortest Path \n";
            cout << "2. View City Map\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    user.findOptimalPath();
                    break;
                case 2:
                    user.viewMap();
                    break;
                case 3:
                    cout << "Exiting User Menu...\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        } while (choice != 3);
    }

// Function to display admin menu
void showAdminMenu() {
    AdminController admin;
    int choice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Location\n";
        cout << "2. Add Road\n";
        cout << "3. Remove Location\n";
        cout << "4. Remove Road\n";
        cout << "5. View City Map\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                admin.addaLocation();
                break;
            case 2:
                admin.addaRoute();
                break;
            case 3:
                admin.removeaLocation();
                break;
            case 4:
                admin.removeaRoute();
                break;
            case 5:
                admin.viewMap();
                break;
            case 6:
                cout << "Exiting Admin Menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
}

};

int main() {
    int choice;
    BusReservationSystem brs;
    TrainReservationSystem trs;
    TrafficManagementSystem tms;
    // Assume you have a class for traffic congestion management.

    cout << "Welcome to Belagavi Smart City Management System\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Bus Reservation System\n";
        cout << "2. Train Reservation System\n";
        cout << "3. Path Finding Management system\n";
        cout << "4. Residence Management System\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input. Please enter a valid choice.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nWelcome to the Bus Reservation System!\n";
                brs.run();
                break;

            case 2:
                cout << "\nWelcome to the Train Reservation System!\n";
                trs.run();
                break;

            case 3:
                cout << "\nWelcome to the Path finding Management System!\n";
                tms.run();  // Call a function to handle traffic congestion logic.
                break;

            case 4: 
                cout<< "\nResidence Management System! \n";
                manageAccommodation();
                break;


            case 5:
                cout << "\nThank you for using Belagavi Smart City Management System. Goodbye!\n";
                break;
    

            default:
                cout << "\nInvalid choice. Please select a valid option.\n";
        }
    } while (choice != 5);

    return 0;
}
