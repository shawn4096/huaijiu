// chuzi.c ����

inherit NPC;
//inherit F_VENDOR;

int give_food();
int give_water();

void create()
{
	set_name("����", ({ "chuzi" }) );
	set("gender", "����" );
	set("age", 34);
	set("long",
		"����һλ�����̳�����Ĵ�ʦ��������æµ�����ղˣ����������Ҫfood��water��\n");
	set("combat_exp", 0);
	set("attitude", "peaceful");
	/*set("rank_info/respect", "����");
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
	tell_object(ob,me->name()+"����һ�����ӡ�\n");
	return 1;
}

int give_water()
{
	object ob=this_player();
	object me=this_object();
	object obj;
	
	obj=new("/d/sld/npc/obj/jiudai");
	obj->move(ob);
	tell_object(ob,me->name()+"����һ���ƴ���\n");
	return 1;
}