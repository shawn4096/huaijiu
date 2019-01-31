// caiji@SJ 8/25/2000
// for a job

#include <room.h>
inherit ROOM;

int do_add(string);
int do_jian(string);

void create ()
{
	set ("short", "ҩ®");
	set ("long", @LONG
�����������ɵ�ҩ®�����޵����Ը��ײ��߼��࣬������ҽ��ᣬ����
Ҳ�������ˣ�����׼����һЩ��ҩ�����ڹ����ϡ����ӽ��䴦����һ�ڴ�
������guo���������޵����Լ�����ҩ�õġ�
LONG);

	set("item_desc", 
	(["guo" : 
	     " һ�ڴ�������������Ŷ�����(fang)����ҩ��(ao yao)��\n", 
	]));



	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"ryd",
	]));
	
	/*set("objects", 
	([ //sizeof() == 1
		MEDICINE_D("jinchuang") : 3,
	]));*/

	set("resource", ([ /* sizeof() == 1 */
	 "water" : 1,
	 ]));
	  set("coor/x",-300);
	  set("coor/y",200);
	  set("coor/z",10);

	set("no_clean_up", 0);
	set("cook/allow",0);
	set("cook/wugong",0);
	set("cook/zhizhu",0);
	set("cook/shachong",0);
	set("cook/xiezi",0);
	set("last_put",0);

	setup();
}


void init()
{					     
	add_action("do_add", "fang");
	add_action("do_add", "add");
	add_action("do_jian", "jian");
	add_action("do_jian", "ao");
}

int do_add(string arg)
{
	string item_name;
	object who = this_player();
	object me = this_object();
	object item;
	mapping fam=who->query("family");
	if (me->is_busy()) return notify_fail("��������æ���أ�\n");
	if (!fam || fam["family_name"] !="������"){
		return notify_fail("�㲻�����޵��ӣ����������ﰾҩ��\n");
	}
	if(!arg) return notify_fail("��Ҫ��ʲô�����ӽ����\n");
	if( sscanf(arg, "%s in guo", item_name)!=1 )
		return notify_fail("�÷���fang <����> in guo��\n");

	if (item_name=="water")
	  {
	  message_vision( "$N������Ҩ��һ��ˮ��\n",who);
	  me->set("cook/allow",1);
	  return 1;
	  }

	item=present(item_name, who);
	if (! present(item_name, who)) return notify_fail("������û���ⶫ����\n");

	if ( item->query("cook/allow") !=1 ) 
	return notify_fail("�����������ҩ�ģ���ʲô�����������ӡ�\n");
	message_vision( "$N��һ"+item->query("unit")+item->query("name")+"�ӽ����\n",who);
	set("item_desc", 
	(["guo" :  " һ�ڴ���������ҩ��(ao yao)���������߰���Ĳ�֪��(fang)��Щʲô��\n",  ]));
	if ( (!item->query("cook/owner")) || item->query("cook/owner")!=who->query("id")) 
	return notify_fail("������͵��˭�Ķ�������������ذ���\n");

	if ( ( me->query("last_put") )&& me->query("last_put")!=who->query("id")) 
	return notify_fail("���˻�û����ҩ�أ������˼����ҡ�\n");


	if (me->query("cook/"+item->query("cook/type")) < item->query("cook/value"))
	   me->set("cook/"+item->query("cook/type"),item->query("cook/value"));
	   me->set("last_put",who->query("id"));
	destruct(item);
	return 1;
}

int do_jian(string arg)
{
	object me = this_object();
	object who = this_player();
	object gao;
	mapping fam=who->query("family");
	int prices;
	if (who->is_busy()) return notify_fail("��������æ���أ�\n");
	if (!fam || fam["family_name"] !="������"){
		return notify_fail("�㲻�����޵��ӣ����������ﰾҩ��\n");
	}
	if(!arg || arg != "yao") return notify_fail("��ɶ��\n");
	if ( !me->query("cook/allow") ) return notify_fail("������ˮ��û�У���ô��ҩ��\n");

	prices=me->query("cook/xiezi")*me->query("cook/shachong")
	      *me->query("cook/zhizhu")*me->query("cook/wugong");

	if(!prices ) gao=new("/d/xingxiu/obj/yao");
	else {gao=new("/d/xingxiu/obj/gao");

	if(prices<10 && prices>0 )prices=10+random(10);
	if(prices>200)prices=200+random(100);
	gao->set("xx/owner",who);
	gao->set("prices",prices);
	gao->set("long",gao->query("long")+"�����������ɵ�"+who->name()+"��ҩ®�������ģ�\n");
	}
	message_vision( "$N�ڹ�����ҽ��˽���Ȼ�󰾰������������������ڰ�����"+gao->query("name")+"��\n",who);
	who->start_busy(2+random(3));
	gao->move(who);

	me->set("cook/allow",0);
	me->set("cook/wugong",0);
	me->set("cook/zhizhu",0);
	me->set("cook/shachong",0);
	me->set("cook/xiezi",0);
	me->set("last_put",0);

	me->set("item_desc", 
	(["guo" : 
	     " һ�ڴ�������������Ӷ�����(add)����ҩ��(ao yao)��\n", 
	]));

	return 1;
}
