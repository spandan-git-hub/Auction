#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>

using namespace std;

struct Bid {
    string bidderName;
    float amount;
    Bid(string name, float amt) : bidderName(name), amount(amt) {}
};

struct CompareBid {
    bool operator()(const Bid& a, const Bid& b) {
        return a.amount < b.amount;
    }
};

struct Product {
    string name;
    string description;
    string imagePath;
    float minPrice;
};

int main() {
    int numBidders;
    vector<string> bidderAccounts;

    cout << "Enter number of bidders: ";
    cin >> numBidders;
    cin.ignore();

    cout << "\n--- Bidder Account Creation ---\n";
    for (int i = 0; i < numBidders; ++i) {
        string name;
        cout << "Enter name for Bidder " << i + 1 << ": ";
        getline(cin, name);
        bidderAccounts.push_back(name);
    }

    Product product;
    cout << "\n--- Product Upload by Seller ---\n";
    cout << "Enter Product Name: ";
    getline(cin, product.name);

    cout << "Enter Product Description: ";
    getline(cin, product.description);

    cout << "Enter Product Image Path (e.g., product.jpg): ";
    getline(cin, product.imagePath);

    cout << "Enter Minimum Bidding Price: Rs.";
    cin >> product.minPrice;

    cout << "\nProduct has been successfully uploaded.";
    cout << "\nProduct: " << product.name
         << "\nDescription: " << product.description
         << "\nImage: " << product.imagePath
         << "\nMinimum Price: Rs." << product.minPrice << endl;

    cout << "\n--- Bidding Starts ---\n";

    priority_queue<Bid, vector<Bid>, CompareBid> bidQueue;

    for (int round = 1;; ++round) {
        cout << "\nBidding Round " << round << ":\n";
        bool anyBidPlaced = false;

        for (int i = 0; i < numBidders; ++i) {
            if (bidderAccounts[i].empty()) continue;

            float bidAmount;
            cout << bidderAccounts[i] << ", enter your bid (or -1 to exit): $";
            cin >> bidAmount;

            if (bidAmount == -1) {
                cout << bidderAccounts[i] << " has exited the bidding.\n";
                bidderAccounts[i] = "";
                continue;
            }

            if (bidAmount < product.minPrice) {
                cout << "Bid is below minimum price. Try again in next round.\n";
                continue;
            }

            bidQueue.push(Bid(bidderAccounts[i], bidAmount));
            anyBidPlaced = true;
        }

        bool allExited = true;
        for (const auto& name : bidderAccounts) {
            if (!name.empty()) {
                allExited = false;
                break;
            }
        }

        if (allExited || !anyBidPlaced) {
            cout << "\nBidding Ended. No active bidders left.\n";
            break;
        }

        char cont;
        cout << "Do you want to continue to next round? (y/n): ";
        cin >> cont;
        if (cont == 'n' || cont == 'N') break;
    }

    if (!bidQueue.empty()) {
        Bid winner = bidQueue.top();
        cout << "\nWinner: " << winner.bidderName << " with a bid of Rs." << winner.amount << endl;
        cout << "Product \"" << product.name << "\" is sold to " << winner.bidderName << ".\n";
        cout << "Image Path: " << product.imagePath << "\n";
    } else {
        cout << "\nNo valid bids were placed. Product not sold.\n";
    }

    return 0;
}
