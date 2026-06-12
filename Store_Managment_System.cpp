#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ================= PRODUCT CLASS ==================
class Product
{
private:
    string category;
    string name;
    int price;
    int quantity;

public:
//default constructor
    Product()
    {
        category = "";
        name = "";
        price = 0;
        quantity = 0;
    }

    Product(string c, string n, int p, int q)
    {
        category = c;
        name = n;
        price = p;
        quantity = q;
    }

    void display()
    {
        cout << "\nProduct: " << name;
        cout << "\nCategory: " << category;
        cout << "\nPrice: Rs." << price;
        cout << "\nAvailable Quantity: " << quantity << endl;
    }

    string getName()
    {
        return name;
    }

    int getPrice()
    {
        return price;
    }

    int getQuantity()
    {
        return quantity;
    }

    void reduceQuantity(int q)
    {
        quantity -= q;
    }

    void increaseQuantity(int q)
    {
        quantity += q;
    }
};

// ================= CART CLASS =================
class Cart
{
private:
    Product items[20];
    int quantities[20];
    int categoryIndex[20];
    int productIndex[20];
    int count;

public:
    Cart()
    {
        count = 0;
    }

    void addToCart(Product p, int q, int cIndex, int pIndex)
    {
        if(count >= 20)
            throw string("Cart is full!");

        if(q <= 0)
            throw string("Invalid quantity!");

        if(q > p.getQuantity())
            throw string("Not enough stock available!");

        items[count] = p;
        quantities[count] = q;
        categoryIndex[count] = cIndex;
        productIndex[count] = pIndex;
        count++;

        cout << "\nProduct added to cart successfully!\n";
    }

    void showCart()
    {
        if(count == 0)
        {
            cout << "\nCart is empty!\n";
            return;
        }

        cout << "\n========== CART ==========\n";

        for(int i = 0; i < count; i++)
        {
            cout << "\nItem " << i + 1;
            cout << "\nProduct: " << items[i].getName();
            cout << "\nQuantity: " << quantities[i];
            cout << "\nPrice Per Item: Rs." << items[i].getPrice();
            cout << "\nSubtotal: Rs." << items[i].getPrice() * quantities[i] << endl;
        }

        cout << "\nTotal Bill: Rs." << calculateTotal() << endl;
    }

    int calculateTotal()
    {
        int total = 0;

        for(int i = 0; i < count; i++)
            total += items[i].getPrice() * quantities[i];

        return total;
    }

    int getCount()
    {
        return count;
    }

    Product getItem(int index)
    {
        return items[index];
    }

    int getQuantity(int index)
    {
        return quantities[index];
    }

    int getCategoryIndex(int index)
    {
        return categoryIndex[index];
    }

    int getProductIndex(int index)
    {
        return productIndex[index];
    }

    void clearCart()
    {
        count = 0;
    }
};

// ================= PURCHASE HISTORY CLASS =================
class PurchaseHistory
{
private:
    Product purchasedItems[20];
    int purchasedQuantities[20];
    int categoryIndex[20];
    int productIndex[20];
    int count;
    string customerName;

public:
    PurchaseHistory()
    {
        count = 0;
        customerName = "";
    }

    void savePurchasedItems(string name, Cart &cart)
    {
        customerName = name;
        count = cart.getCount();

        for(int i = 0; i < count; i++)
        {
            purchasedItems[i] = cart.getItem(i);
            purchasedQuantities[i] = cart.getQuantity(i);
            categoryIndex[i] = cart.getCategoryIndex(i);
            productIndex[i] = cart.getProductIndex(i);
        }
    }

    void showPurchasedItems()
    {
        if(count == 0)
        {
            throw string("No checked out products found!");
        }

        cout << "\n========== CHECKED OUT PRODUCTS ==========\n";

        for(int i = 0; i < count; i++)
        {
            if(purchasedQuantities[i] > 0)
            {
                cout << "\nItem " << i + 1;
                cout << "\nProduct: " << purchasedItems[i].getName();
                cout << "\nQuantity Bought: " << purchasedQuantities[i];
                cout << "\nPrice Per Item: Rs." << purchasedItems[i].getPrice() << endl;
            }
        }
    }

    int getCount()
    {
        return count;
    }

    int getPurchasedQuantity(int index)
    {
        return purchasedQuantities[index];
    }

    Product getPurchasedItem(int index)
    {
        return purchasedItems[index];
    }

    int getCategoryIndex(int index)
    {
        return categoryIndex[index];
    }

    int getProductIndex(int index)
    {
        return productIndex[index];
    }

    void reducePurchasedQuantity(int index, int qty)
    {
        purchasedQuantities[index] -= qty;
    }
};

// ================= WISHLIST CLASS =================
class Wishlist
{
private:
    Product items[20];
    int count;

public:
    Wishlist()
    {
        count = 0;
    }

    void addToWishlist(Product p)
    {
        if(count >= 20)
            throw string("Wishlist is full!");

        items[count] = p;
        count++;

        cout << "\nProduct added to wishlist!\n";
    }

    void showWishlist()
    {
        if(count == 0)
        {
            cout << "\nWishlist is empty!\n";
            return;
        }

        cout << "\n========== WISHLIST ==========\n";

        for(int i = 0; i < count; i++)
        {
            cout << "\nItem " << i + 1 << endl;
            items[i].display();
        }
    }
};

// ================= USER CLASS =================
class User
{
protected:
    string name;
    string email;

public:
    void setUser(string n, string e)
    {
        name = n;
        email = e;
    }

    virtual float applyDiscount(float total)
    {
        return total;
    }
};

// ================= STUDENT CLASS =================
class Student : public User
{
private:
    string schoolName;
    string rollNumber;

public:
    void setStudentData(string school, string roll)
    {
        schoolName = school;
        rollNumber = roll;
    }

    float applyDiscount(float total)
    {
        return total - (total * 0.15);
    }

    void showStudentData()
    {
        cout << "\nStudent verified!";
        cout << "\nSchool Name: " << schoolName;
        cout << "\nRoll Number: " << rollNumber << endl;
    }
};

// ================= ORDER CLASS =================
class Order
{
public:
    void saveOrder(string customerName, string email, Cart &cart, float finalBill)
    {
        ofstream file("orders.txt", ios::app);

        if(!file)
            throw string("Unable to open orders file!");

        file << "\n========== ORDER ==========\n";
        file << "Customer Name: " << customerName << endl;
        file << "Email: " << email << endl;

        for(int i = 0; i < cart.getCount(); i++)
        {
            file << cart.getItem(i).getName()
                 << " | Quantity: " << cart.getQuantity(i)
                 << " | Price: Rs." << cart.getItem(i).getPrice()
                 << endl;
        }

        file << "Final Bill: Rs." << finalBill << endl;
        file << "===========================\n";

        file.close();
    }

    void saveRefund(string customerName, Product p, int qty)
    {
        ofstream file("refunds.txt", ios::app);

        if(!file)
            throw string("Unable to open refunds file!");

        file << "\n========== REFUND ==========\n";
        file << "Customer Name: " << customerName << endl;
        file << "Returned Product: " << p.getName() << endl;
        file << "Returned Quantity: " << qty << endl;
        file << "Refund Amount: Rs." << p.getPrice() * qty << endl;
        file << "Status: Refund Completed" << endl;
        file << "============================\n";

        file.close();
    }
};

// ================= FUNCTIONS =================
void displayProducts(Product products[])
{
    for(int i = 0; i < 3; i++)
    {
        cout << "\nProduct " << i + 1 << endl;
        products[i].display();
    }
}

void showFullInventory(Product shirts[], Product pants[], Product hoodies[], Product shoes[])
{
    cout << "\n========== FULL INVENTORY ==========\n";

    cout << "\n\n--- SHIRTS ---\n";
    displayProducts(shirts);

    cout << "\n\n--- PANTS ---\n";
    displayProducts(pants);

    cout << "\n\n--- HOODIES ---\n";
    displayProducts(hoodies);

    cout << "\n\n--- SHOES ---\n";
    displayProducts(shoes);
}

// ================= MAIN FUNCTION =================
int main()
{
    Product shirts[3] =
    {
        Product("Shirts", "Black Oversized Tee", 2500, 10),
        Product("Shirts", "White Graphic Tee", 3000, 8),
        Product("Shirts", "Charcoal Flannel Shirt", 2800, 7)
    };

    Product pants[3] =
    {
        Product("Pants", "Black Cargo Pants", 4000, 6),
        Product("Pants", "Baggy Denim Jeans", 3500, 9),
        Product("Pants", "Straight Fit Trousers", 3200, 5)
    };

    Product hoodies[3] =
    {
        Product("Hoodies", "Grey Oversized Hoodie", 5000, 4),
        Product("Hoodies", "Black Zip Hoodie", 4800, 6),
        Product("Hoodies", "Brown Pullover Hoodie", 4500, 5)
    };

    Product shoes[3] =
    {
        Product("Shoes", "White Sneakers", 6500, 7),
        Product("Shoes", "Black Running Shoes", 7000, 5),
        Product("Shoes", "Casual Trainers", 6200, 6)
    };

    Cart cart;
    Wishlist wishlist;
    Order order;
    PurchaseHistory history;

    int choice;

    while(true)
    {
        try
        {
            cout << "\n========== CASUAL WEAR STORE ==========\n";
            cout << "1. Shirts\n";
            cout << "2. Pants\n";
            cout << "3. Hoodies\n";
            cout << "4. Shoes\n";
            cout << "5. View Cart\n";
            cout << "6. View Wishlist\n";
            cout << "7. Refund\n";
            cout << "8. Checkout\n";
            cout << "9. View Inventory\n";
            cout << "10. Exit Site\n";

            cout << "\nEnter Choice: ";
            cin >> choice;

            if(choice < 1 || choice > 10)
                throw string("Invalid menu choice!");

            Product selected;
            int productChoice, action, qty;
            int categoryNo = 0;

            if(choice >= 1 && choice <= 4)
            {
                switch(choice)
                {
                    case 1:
                        categoryNo = 1;
                        cout << "\n========== SHIRTS ==========\n";
                        displayProducts(shirts);
                        break;

                    case 2:
                        categoryNo = 2;
                        cout << "\n========== PANTS ==========\n";
                        displayProducts(pants);
                        break;

                    case 3:
                        categoryNo = 3;
                        cout << "\n========== HOODIES ==========\n";
                        displayProducts(hoodies);
                        break;

                    case 4:
                        categoryNo = 4;
                        cout << "\n========== SHOES ==========\n";
                        displayProducts(shoes);
                        break;
                }

                cout << "\nSelect Product: ";
                cin >> productChoice;

                if(productChoice < 1 || productChoice > 3)
                    throw string("Invalid product choice!");

                switch(categoryNo)
                {
                    case 1:
                        selected = shirts[productChoice - 1];
                        break;

                    case 2:
                        selected = pants[productChoice - 1];
                        break;

                    case 3:
                        selected = hoodies[productChoice - 1];
                        break;

                    case 4:
                        selected = shoes[productChoice - 1];
                        break;
                }

                cout << "\n1. Add To Cart";
                cout << "\n2. Add To Wishlist";
                cout << "\nEnter Choice: ";
                cin >> action;

                switch(action)
                {
                    case 1:
                        cout << "\nEnter Quantity: ";
                        cin >> qty;

                        cart.addToCart(selected, qty, categoryNo, productChoice - 1);
                        break;

                    case 2:
                        wishlist.addToWishlist(selected);
                        break;

                    default:
                        throw string("Invalid action!");
                }
            }

            else if(choice == 5)
            {
                cart.showCart();
            }

            else if(choice == 6)
            {
                wishlist.showWishlist();
            }

            else if(choice == 7)
            {
                if(history.getCount() == 0)
                    throw string("No previous checkout found for refund!");

                string refundName;

                cin.ignore();

                cout << "\nEnter Your Name For Refund: ";
                getline(cin, refundName);

                history.showPurchasedItems();

                int returnChoice, returnQty;

                cout << "\nSelect Product To Return: ";
                cin >> returnChoice;

                if(returnChoice < 1 || returnChoice > history.getCount())
                    throw string("Invalid return product choice!");

                int index = returnChoice - 1;

                if(history.getPurchasedQuantity(index) <= 0)
                    throw string("This product has already been fully refunded!");

                cout << "Enter Quantity To Return: ";
                cin >> returnQty;

                if(returnQty <= 0)
                    throw string("Invalid return quantity!");

                if(returnQty > history.getPurchasedQuantity(index))
                    throw string("You cannot return more than purchased quantity!");

                int c = history.getCategoryIndex(index);
                int p = history.getProductIndex(index);

                switch(c)
                {
                    case 1:
                        shirts[p].increaseQuantity(returnQty);
                        break;

                    case 2:
                        pants[p].increaseQuantity(returnQty);
                        break;

                    case 3:
                        hoodies[p].increaseQuantity(returnQty);
                        break;

                    case 4:
                        shoes[p].increaseQuantity(returnQty);
                        break;
                }

                Product returnedProduct = history.getPurchasedItem(index);

                history.reducePurchasedQuantity(index, returnQty);
                order.saveRefund(refundName, returnedProduct, returnQty);

                cout << "\nRefund completed successfully!";
                cout << "\nReturned Product: " << returnedProduct.getName();
                cout << "\nReturned Quantity: " << returnQty;
                cout << "\nRefund Amount: Rs." << returnedProduct.getPrice() * returnQty;
                cout << "\nInventory updated!\n";
            }

            else if(choice == 8)
            {
                if(cart.getCount() == 0)
                    throw string("Cannot checkout. Cart is empty!");

                string name, email;

                cin.ignore();

                cout << "\nEnter Name: ";
                getline(cin, name);

                cout << "Enter Email: ";
                getline(cin, email);

                int userType;

                cout << "\n1. Regular Customer";
                cout << "\n2. Student";
                cout << "\nEnter Choice: ";
                cin >> userType;

                float total = cart.calculateTotal();
                float finalBill = total;

                if(userType == 2)
                {
                    Student s;
                    string school, roll;

                    s.setUser(name, email);

                    cin.ignore();

                    cout << "\nEnter School Name: ";
                    getline(cin, school);

                    cout << "Enter Roll Number: ";
                    getline(cin, roll);

                    s.setStudentData(school, roll);
                    s.showStudentData();

                    finalBill = s.applyDiscount(total);

                    cout << "\n15% Student Discount Applied!\n";
                }

                for(int i = 0; i < cart.getCount(); i++)
                {
                    int c = cart.getCategoryIndex(i);
                    int p = cart.getProductIndex(i);
                    int q = cart.getQuantity(i);

                    switch(c)
                    {
                        case 1:
                            shirts[p].reduceQuantity(q);
                            break;

                        case 2:
                            pants[p].reduceQuantity(q);
                            break;

                        case 3:
                            hoodies[p].reduceQuantity(q);
                            break;

                        case 4:
                            shoes[p].reduceQuantity(q);
                            break;
                    }
                }

                history.savePurchasedItems(name, cart);

                cout << "\n========== FINAL BILL ==========\n";
                cout << "Original Total: Rs." << total;
                cout << "\nFinal Total: Rs." << finalBill << endl;

                order.saveOrder(name, email, cart, finalBill);
                cart.clearCart();

                cout << "\nOrder placed successfully!";
                cout << "\nInventory updated!";
                cout << "\nReturning to store menu...\n";
            }

            else if(choice == 9)
            {
                showFullInventory(shirts, pants, hoodies, shoes);
            }

            else if(choice == 10)
            {
                cout << "\nExiting Site...";
                cout << "\nThank you for visiting!\n";
                break;
            }
        }

        catch(string message)
        {
            cout << "\nException: " << message << endl;
        }
}
    return 0;
}
