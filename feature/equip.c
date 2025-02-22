// equip.c
// Modify by snowman@SJ 22/02/2000

#include <ansi.h>
#include <dbase.h>
#include <weapon.h>

int wear()
{
	object owner;
	mapping armor_prop, applied_prop;
	string *apply, type;

	// Only character object can wear armors.
    	if (!environment()) return 0;
	if( !(owner = environment())->is_character()) return 0;

	// If already worn, just recognize it.
	if( query("equipped") ) return 1;

	// Check if we have "armor_prop" defined.
	type = query("armor_type");
	if (!type || !mapp(armor_prop = query("armor_prop")))
		return notify_fail("你只能穿戴可当作护具的东西。\n");

	if( owner->query_temp("armor/" + type) )
		return notify_fail("你已经穿戴了同类型的护具了。\n");

	owner->set_temp("armor/" + type, this_object());
	apply = keys(armor_prop);
	applied_prop = owner->query_temp("apply");
	if( !mapp(applied_prop) ) applied_prop = ([]);
	for(int i = 0; i<sizeof(apply); i++)
		if( undefinedp(applied_prop[apply[i]]) )
			applied_prop[apply[i]] = armor_prop[apply[i]];
		else
			applied_prop[apply[i]] += armor_prop[apply[i]];
	owner->set_temp("apply", applied_prop);
	set("equipped", "worn");
	return 1;
}

int wield()
{
	object owner, old_weapon;
	mapping weapon_prop;
	string *apply;
	int flag;

	// Only character object can wear armors.
    	if (!environment()) return 0;
	if( !(owner = environment())->is_character() ) return 0;

	// If already wielded, just recognize it.
	if( query("equipped") ) return 1;

	// Check if we have "weapon_prop" defined.
	if (!query("skill_type") || !mapp(weapon_prop = query("weapon_prop")))
		return notify_fail("你只能装备可当作武器的东西。\n");

	if( query("broken") ) return notify_fail("这件武器已经损坏了。\n");
	flag = query("flag");

	if( flag & TWO_HANDED ) {
		if( owner->query_temp("weapon")
		||      owner->query_temp("secondary_weapon")
		||      owner->query_temp("armor/shield") )
			return notify_fail("你必须空出双手才能装备双手武器。\n");
		owner->set_temp("weapon", this_object());
	} else {

		// If we are are using any weapon?
		if( !(old_weapon = owner->query_temp("weapon")) )
			owner->set_temp("weapon", this_object());

		else // If we still have a free hand? 
		if( !owner->query_temp("secondary_weapon")
		&&      !owner->query_temp("armor/shield") ) {

			// If we can wield this as secondary weapon?
			if(flag & SECONDARY) {
				owner->set_temp("secondary_weapon", this_object());
			// If we can switch our old weapon to secondary weapon ?
			} else if( (int)old_weapon->query("flag") & SECONDARY ) {
				old_weapon->unequip();
				owner->set_temp("weapon", this_object());
				old_weapon->wield();
			// We need unwield our old weapon before we can use this one.
			} else
				return notify_fail("你必须先放下你目前装备的武器。\n");

		// We have both hands wearing something.
		} else
			return notify_fail("你必须空出一只手来使用武器。\n");
	}

	apply = keys(weapon_prop);
	for(int i = 0; i<sizeof(apply); i++)
		owner->add_temp("apply/" + apply[i], weapon_prop[apply[i]]);
	
	owner->reset_action();
	set("equipped", "wielded");
	return 1;
}

int unequip()
{
	object owner;
	mapping prop, applied_prop;
	string *apply, equipped;

	if( !(owner = environment()) ) return 0;

	if( !stringp(equipped = query("equipped")) )
		return notify_fail("你目前并没有装备这样东西。\n");

	if( equipped=="wielded" ) {
		if( (object)owner->query_temp("weapon") == this_object() )
			owner->delete_temp("weapon");
		else if( (object)owner->query_temp("secondary_weapon") == this_object() )
			owner->delete_temp("secondary_weapon");
		prop = query("weapon_prop");
		owner->reset_action();
	} else if( equipped=="worn" ) {
		owner->delete_temp("armor/" + query("armor_type") );
		prop = query("armor_prop");
	}

	apply = keys(prop);
	applied_prop = owner->query_temp("apply");
	if (!applied_prop) applied_prop = ([]);
	for(int i = 0; i<sizeof(apply); i++)
		// To support array apply, we cannot add_temp() here.
		applied_prop[apply[i]] -= prop[apply[i]];
	
	delete("equipped");
	return 1;
}

int broken(string str)
{
	object weapon, victim;
	
	weapon = this_object();
	victim = environment(this_object());
		 
	if( weapon->query("no_broken") ) return 0;
	weapon->unequip();
	
	if(victim->is_character()){
		weapon->move(environment(victim));
	     	victim->reset_action();
	}
	
	if( !str ) str = "损坏的";

	weapon->delete_temp("apply");
	weapon->set_temp("apply/name_old", weapon->name());
	weapon->set_temp("apply/weapon_prop_old", weapon->query("weapon_prop"));
	weapon->set_temp("apply/long_old", weapon->query("long"));
	weapon->set_temp("apply/value", weapon->query("value"));
	weapon->set("name", str + weapon->query("name"));

	weapon->set("value", 49);
	weapon->set("broken", 1);
	weapon->set("weapon_prop", 0);
	weapon->set("treasure", -1);
	weapon->set("long", weapon->query("long")+"\n但是它已经损坏，再也无法使用了。\n");

	return 1;
}


int do_embed(object me)
{
    	object ob;
    	ob = this_object();
  
    	if( !ob->query("embedded") || !me) return 0;
    
    	if(environment(ob) != me 
       	|| me->is_ghost() 
       	|| !me->query_temp("embed")){
	    	delete("embedded");
	      	return 0;
	}
	
    	me->receive_wound("qi", ob->query("damage")*2, "身中"+ob->name()+"而");
	me->receive_damage("qi", ob->query("damage")*4, "身中"+ob->name()+"而");
	tell_object(me, HIR "鲜血正顺着你身上的"+ob->name()+HIR"嘀嗒嘀嗒地直往下流！\n" NOR );
	tell_room(environment(me), HIR + "鲜血顺着"+me->name()+HIR"身上的"+ob->name()+HIR"直往下流！\n" NOR, ({ me }));  
	call_out("do_embed", 15+random(10), me);
	
    	return 1;
}

