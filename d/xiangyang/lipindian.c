#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��Ʒ��");
        set("long", @LONG
һ��СС����Ʒ�꣬��̨���������ĸ������ӣ�����ֱ�д��
���������ǡ����ԡ�������������ʢ�Ŵ�����͵���Ʒ�����
�Է���(put)��Ʒ��ȥ��
LONG
        );

		set("item_desc",([
        "put" : "�﷨��put <����>������������Ǳ���(str)������(con)������(int)����(dex)��\n",
        ]));

        set("exits", ([ 
          "out" : "/d/xiangyang/cross2",
]));

        setup();
}
void init()
{
	object me=this_player();
	
	if( userp(me) ) {
		if( me->query("str")>30 ) {
			me->set("str",30);
			tell_object(me,"��ı����Ѿ����Զ�����Ϊ30��\n");
		}
		if( me->query("con")>30 ) {
			me->set("con",30);
			tell_object(me,"��ĸ����Ѿ����Զ�����Ϊ30��\n");
		}
		if( me->query("int")>30 ) {
			me->set("int",30);
			tell_object(me,"��������Ѿ����Զ�����Ϊ30��\n");
		}
		if( me->query("dex")>30 ) {
			me->set("dex",30);
			tell_object(me,"������Ѿ����Զ�����Ϊ30��\n");
		}
	}
    add_action("do_put", ({ "put", "fang" }));
	return;
} 

int do_put(string arg)
{
       object me;
       me = this_player(); 

	   if(!arg) return notify_fail("��Ҫ�Ž�ȥʲô��Ʒ��\n");
	   if( me->query("str")+me->query("con")+me->query("int")
		   +me->query("dex") <= 80 ) {
		   tell_object(me,"���������ô���������\n");
		   return 1;
	   }
	   if( arg=="����" || arg=="str" ) {
		   if( me->query("str")<=10 ) {
				tell_object(me,"���Ѿ��޷����������Լ��ı����ˡ�\n");
				return 1;
		   }
			me->set("str",me->query("str")-1);
			message_vision("$N�������ó�һ��������������\n",me);
			return 1;
	   }
	   else if( arg=="����" || arg=="con" ) {
		   if( me->query("con")<=10 ) {
				tell_object(me,"���Ѿ��޷����������Լ��ĸ����ˡ�\n");
				return 1;
		   }
			me->set("con",me->query("con")-1);
			message_vision("$N�������ó�һ����Ƿ��������\n",me);
			return 1;
	   }
	   else if( arg=="����" || arg=="int" ) {
		   if( me->query("int")<=10 ) {
				tell_object(me,"���Ѿ��޷����������Լ��������ˡ�\n");
				return 1;
		   }
			me->set("int",me->query("int")-1);
			message_vision("$N�������ó�һ�����Է��������\n",me);
			return 1;
	   }
	   else if( arg=="��" || arg=="dex" ) {
		   if( me->query("dex")<=10 ) {
				tell_object(me,"���Ѿ��޷����������Լ������ˡ�\n");
				return 1;
		   }
			me->set("dex",me->query("dex")-1);
			message_vision("$N�������ó�һ�������������\n",me);
			return 1;
	   }
	   else {
			tell_object(me,"������ܵ���Ʒֻ�б���(str)������(con)������(int)����(dex)��\n");
			return 1;
		   }
}


int get_object(object ob)
{ 
        if(userp(ob))
        return 1;
        return 0;
}

int valid_leave(object me, string dir)
{
	object *obj;

        if(!wizardp(me)&& (me->query("str")+me->query("con")+me->query("int")
                +me->query("dex")>80))
        return notify_fail("���͵��񻹲��������ܳ�ȥ��\n");
	 obj = filter_array(deep_inventory(me),(:get_object:));
    if( sizeof(obj) ) 
		return notify_fail("�����ף�û��ô���ס�\n");
	
	return ::valid_leave(me, dir);
}
