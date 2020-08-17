from restaurant import *
from parlor import *

restaurant_name = input("What's your restaurant's name? ").title()
restaurant_style = input("What style of cuisine does your restaurant serve? ").title()
parlor_base_price = float(input("What's the base price for a serving from your ice cream menu? "))
parlor_size_premium = float(input("What's the price premium for size increases? "))
parlor_scoop_premium = float(input("What's the price premium for scoop additions? "))

my_restaurant = IceCreamParlor(restaurant_name, restaurant_style, parlor_base_price, parlor_scoop_premium, parlor_scoop_premium)
my_restaurant.load_menu()
my_restaurant.get_stored_flavors()

while True:
	general_query = input("""
	
	What would you like to do?
	    
	    load menu  *  update menu  *  print menu

	    take stock  *  decrement stock  *  restock

	    customer order

	    load flavors  *  update flavors  *  describe flavors

	    customer ticket

	    """).lower()
	if general_query == "q":
		break
	elif general_query == "load menu":
		my_restaurant.load_menu()
	elif general_query == "update menu":
		my_restaurant.update_menu()
	elif general_query == "print menu":
		my_restaurant.print_menu()
	elif general_query == "take stock":
		my_restaurant.take_stock()
	elif general_query == "decrement stock":
		my_restaurant.decrement_stock()
	elif general_query == "restock":
		my_restaurant.restock()
	elif general_query == "customer order":
		my_restaurant.customer_order()
	elif general_query == "load flavors":
		my_restaurant.get_stored_flavors()
	elif general_query == "update flavors":
		my_restaurant.update_flavors()
	elif general_query == "describe flavors":
		my_restaurant.describe_flavors()
	elif general_query == "customer ticket":
		my_restaurant.customer_ticket()