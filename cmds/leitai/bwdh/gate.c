//�Խ�ɽׯ  gate.c

#include <ansi.h>
#include <room.h>

inherit ROOM;
void create()
{
	set("short",HIY"ׯԺ"NOR);
	set("long", @LONG
�����ׯԺ�����������µ��Խ�ɽׯ�ˣ��㲻������һ������ǰ��ɽׯ�ĵ�
�ϴ�ɨ��һ����Ⱦ�����������ɵ�̨�׺������ţ��ź�ľ���ƵĴ��Ž����ţ�ʹ
���޷���Ϥ���ڵ�һ�У����ɶ�ߵ�����ǽ��͸����Ҷ��������ҫ������������
�ž�������ֻ�ŵ�Զ���������������
LONG
	);
        set("exits", ([
		"north" : __DIR__"qianting",
		"out": "/d/city/chmiao",
	]));

	set("no_dig", 1);
        set("no_fight",1);
	set("outdoors", "�Խ�ɽׯ");
	setup();
}

void init()
{
    object me = this_player();
    tell_object(me,BLINK + HIW"��ע�⣬���Ѿ�������"HIG"���Խ�ɽׯ��"HIR"����PK����"HIW"��������������������!\n"NOR);
    tell_object(me,BLINK + HIC"�����뿪�Խ�ɽׯ��ϵͳ����ָ�PK������\n"NOR);

    if(me->query("no_pk")){
        me->set("no_pk_recover",me->query("no_pk"));
        me->delete("no_pk");
    }
    return;
}

int valid_leave(object me, string dir)
{
	object *ob = deep_inventory(me);
	int i = sizeof(ob);
	if( dir == "out") {
		while (i--)
		if( ob[i]->query("secret_obj"))
			return notify_fail("�������ô���صĶ��������뿪�Խ�ɽׯ�ǲ����ܵġ�\n");
	}
        if( dir == "out") {
		if( me->query_condition("killer"))
			return notify_fail("ͨ���������̽��ʱ����������뿪�Խ�ɽׯ��\n");
	}

        if(dir == "out"){
                if(me->query("no_pk_recover")){
                        tell_object(me,BLINK + HIG"���뿪���Խ�ɽׯ��ϵͳ�Զ��ָ�������ϴ��״̬��\n"NOR);
                        me->set("no_pk",me->query("no_pk_recover"));
                        me->delete("no_pk_recover");
                }
        me->clear_condition("sjsz_time");
        me->clear_condition("killer");
        me->remove_all_enemy();
        me->remove_all_killer();

    }

	return ::valid_leave(me, dir);
}
