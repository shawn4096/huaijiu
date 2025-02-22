// combined_item.c

#include <dbase.h>
#include <name.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

nosave int amount;

void setup()
{
}

int query_amount() { return amount; }

private void destruct_me() { destruct(this_object()); }

void set_amount(int v)
{
	if( v < 0 ) error("combine:set_amount less than 1.\n");
	if( v==0 ) {
		destruct(this_object());
		return;
	}
	amount = v;
	set_weight(v * (int)query("base_weight"));
}

void add_amount(int v) { set_amount(amount+v); }

string short()
{
	return chinese_number(query_amount()) + query("base_unit")
		+ ::short();
}

varargs int move(mixed dest, int silent)
{
	object env, *inv;
	int i, total;
	string file;

	if( ::move(dest, silent) ) {
		if( env = environment() ) {
			file = base_name(this_object());
			total = (int)query_amount();
			if (!query("broken")) {
				inv = all_inventory(env);
				for(i=0; i<sizeof(inv); i++) {
					if( inv[i]==this_object() ) continue;
					if( inv[i]->query("broken")) continue;
					if( base_name(inv[i])==file ) {
						total += (int)inv[i]->query_amount();
						destruct(inv[i]);
					}
				}
			}
			set_amount(total);
		}
		return 1;
	}
}
