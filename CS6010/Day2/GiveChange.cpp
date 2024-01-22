//
//  main.cpp
//  GiveChange
//
//  Created by Laura Zhang on 8/23/22.
//

#include <iostream>
using namespace std;

int main() {
    cout << "Enter item price in cents:" << endl;
    int item_price = -1;
    cin >> item_price;
    
    cout << "Enter amount paid in cents:" << endl;
    int amount_paid = -1;
    cin >> amount_paid;
    
    int change = amount_paid - item_price;
    cout << "Change = " << change << " cents" << endl;
    
    int quarter_to_cent = 25;
    int dime_to_cent = 10;
    int nickle_to_cent = 5;
    
    int quarters = change / quarter_to_cent;
    change = change % quarter_to_cent;
    
    int dimes = change / dime_to_cent;
    change = change % dime_to_cent;
    
    int nickles = change / nickle_to_cent;
    change = change % nickle_to_cent;
    
    int pennies = change;
    
    cout << "  Quarters: " << quarters << endl;
    cout << "  Dimes: " << dimes << endl;
    cout << "  Nickles: " << nickles << endl;
    cout << "  Pennies: " << pennies << endl;
    
    return 0;
}
