
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name (HIR BMAG"回天再造丹"NOR, ({ "zaizao dan"}));
	set("long","这是一颗以何首乌、朱果、千年雪莲、冰参，以及空青石乳等旷世灵药炼制而\n成的回天再造丹，吃了以后可以让你的先天属性发生变化。\n");

	set("unit","颗");
	set_weight(100);
	set("value",30);
        set("no_cun", 1);
        set("no_drop", 1);
        set("no_give", 1);
	set("no_get", "这样东西不能离开那儿。\n");
	set("treasure",1);	
	set("degree",1);
	set("desc","可以修改先天属性，不过需要扣除exp");
	set("credit",500);
	
	setup();
}

void init()
{
	add_action("do_eat","fu");  
}

int do_eat(string arg)
{

	object me=this_player();
	    
	if (!arg || arg!="zaizao dan")
      		return notify_fail("请使用 fu zaizao dan来调整先天属性。\n");
        me->set_temp("cgift",1);
        write(HIY"你获得一次调整先天属性的机会，请在下线之前使用cgift指令进行调整。\n"NOR);
        destruct(this_object());
        return 1;   

}