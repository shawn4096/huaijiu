// chuzi.c 厨子

inherit NPC;
//inherit F_VENDOR;

int give_food();
int give_water();

void create()
{
	set_name("厨子", ({ "chuzi" }) );
	set("gender", "男性" );
	set("age", 34);
	set("long",
		"这是一位神龙教厨房里的大师傅，正在忙碌着煮饭烧菜，你可以问他要food和water。\n");
	set("combat_exp", 0);
	set("attitude", "peaceful");
	/*set("rank_info/respect", "商人");
	set("vendor_goods", ([
		"/d/sld/npc/obj/shengzi":10,
                "/clone/misc/fire":10,	
        ]));*/
	set("inquiry", ([
		"food" : (: give_food :),
            	"water" : (: give_water :),
	]) );
        setup();
	//add_money("coin", 90);
}

int give_food()
{
	object ob=this_player();
	object me=this_object();
	object obj;
	
	obj=new("/d/sld/npc/obj/baozi");
	obj->move(ob);
	tell_object(ob,me->name()+"给你一个包子。\n");
	return 1;
}

int give_water()
{
	object ob=this_player();
	object me=this_object();
	object obj;
	
	obj=new("/d/sld/npc/obj/jiudai");
	obj->move(ob);
	tell_object(ob,me->name()+"给你一个酒袋。\n");
	return 1;
}