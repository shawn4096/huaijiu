// Room: /d/dzd/pubu.c

#include <ansi.h>
inherit ROOM;
string * name1 = ({ "СȮ��һ��","����̫��","����С��","÷������"}); 

void create()
{
	set("short","�ٲ�");
	set("long",@LONG
һ���޴��ˮ����ɽ�Ϸ������£��γ�һ���ٲ�������һ���߹�����ɽ�����е�����
����������һ���ؾ��������ǰ���Ƿɽ���ˮ¶����ɽǰƮ�����֮�ڰ�����һƬ����
��Ʈ����ɢ������֮�գ�����ͷף���ʶ�Ŀ��ʹ��������������ɾ���͸��ˮ������
�ɿ���һ�����ڡ�
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"senlin6",	
		"south" : __DIR__"xiliu3",
		"southwest" : __DIR__"caodi3",
	]));
}

void init()
{
	add_action("do_tiao","tiao");
}

int do_tiao(string arg)
{
	object me = this_player();
        object boss;
        string name = name1[random(sizeof(name1))];

	if(me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	if(!arg || arg == "" || arg!="pubu")
		return notify_fail("�������Ķ�����\n");

	message_vision(HIC"$N���������������ٲ��ķ����Ծ��ȥ��\n"NOR, me);
        if ( !me->query_temp("marks/�´�������4") ){
          write(HIR"\n���Ȼ�о��ٲ�֮��ȫ�Ǽ�Ӳ����ʯ�����а���һ�������á���\n"NOR);
          tell_room(environment(me), HIR"\nֻ�������项��һ����"+me->name()+"���絾��һ�㱻�ٲ��ļ���ˮ���������˳�����\n"NOR, ({ me }));
          me->unconcious();
          return 1;
        }

        me->delete_temp("marks/�´�������4");
        me->move(__DIR__"rukou");
        boss = new(__DIR__"npc/boss");
        boss->set_name(name, ({ me->query("id")+"'s boss" }) );
        boss->set_temp("target", getuid(me));
        boss->do_copy(me);
        switch( random(4) ) {
                case 0:  
                        boss->move(__DIR__"shidong1");
                        break;
                case 1:  
                        boss->move(__DIR__"shidong2");
                        break;
                case 2:  
                        boss->move(__DIR__"shidong3");
                        break;
                case 3:  
                        boss->move(__DIR__"shidong4");
                        break;
                default: // others      BUG!!!
                        boss->move(__DIR__"rukou");
        }

        message_vision(HIW"\n$N����������Ծ�����ٲ�֮�У�ʹ�˸���ǧ��׹�������������̣�����վס��\n"NOR, me);
        return 1;
}
	