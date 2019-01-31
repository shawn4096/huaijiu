// Room: /d/city/jiangnan.c

#include <ansi.h>

#define SHIP_TO __DIR__"jiangbei"

inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();

void create()
{
        set("short", "���׽���");
        set("long", @LONG
��һ������ȥ��֮��ǰ��ŭ����ӿ��ˮ���ļ�������һ����(river����
����ɽʯ���������Ρ�룬�������ƣ����ǵ������׽��ϡ�������ʮ���ɸߣ�
��Ҫ�ߵ�������ȴҲ��ʵ���ס� 
LONG
        );

        set("exits", ([
                "west" : __DIR__"xishuang",
        ]));

        set("item_desc", ([
                "river" : "��������һҶС�ۣ�Ҳ��(yell)һ�����Ҿ���������\n",
        ]));

        set("outdoors", "����");
        set("coor/x",-300);
  set("coor/y",-530);
   set("coor/z",0);
   setup();
}

void init()
{
        add_action("do_yell", "yell");
        add_action("du_jiang", "dujiang");
}

void check_trigger()
{
        object room;
        object thisroom = this_object();

        if(!query("exits/enter") ) {
                if( !(room = find_object(__DIR__"duchuan")) )
                        room = load_object(__DIR__"duchuan");
                if( room = find_object(__DIR__"duchuan") ) {
                        if((int)room->query("yell_trigger")==0 ) {
                                room->set("yell_trigger", 1);
                                set("exits/enter", __DIR__"duchuan");
                                room->set("exits/out", __FILE__);
                                message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤�Ű���ϵ̰����Ա�˿����¡�\n", thisroom);
                                message("vision", "������һ��̤�Ű���ϵ̰����γ�һ�����ϵĽ��ݡ�\n", room);
                                remove_call_out("on_board");
                                call_out("on_board", 15);
                        }
                        else
                                message("vision", "ֻ���ý�������������������������æ���š�����\n", thisroom);
                }
                else
                        message("vision", "ERROR: boat not found\n", thisroom);
        }
        else 
                message("vision", "����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n", thisroom);
}

void on_board()
{
        object room;

        if( !query("exits/enter") ) return;

        message("vision", "������̤�Ű��������������һ�㣬��������ʻȥ��\n", this_object());

        if( room = find_object(__DIR__"duchuan") )
        {
                room->delete("exits/out");
                message("vision", "������̤�Ű���������˵��һ��������ඡ������һ�㣬��������ʻȥ��\n", room);
        }
        delete("exits/enter");

        remove_call_out("arrive");
        call_out("arrive", 20);
}

void arrive()
{
        object room;

        if( room = find_object(__DIR__"duchuan") )
        {
                room->set("exits/out", SHIP_TO);
                message("vision", "����˵���������ϰ��ɡ����漴��һ��̤�Ű���ϵ̰���\n", room);
        }
        remove_call_out("close_passage");
        call_out("close_passage", 20);
}

void close_passage()
{
        object room, *ob;
        int i;

        if( room = find_object(__DIR__"duchuan") ) {
                room->delete("exits/out");

                tell_room(room, "��������˵���������´��ɣ���ҲҪ��ȥ�ˡ���\n", ({}));
                ob = all_inventory(room);
                for(i = 0; i < sizeof(ob); i++) {
                        if (userp(ob[i])) {
                                if (!living(ob[i])) message_vision("������$Ņ���˴���\n", ob[i]);
                                else message_vision("$N���������Ļ����ԹԵ����˴���\n", ob[i]);
                                ob[i]->move(SHIP_TO);
                                if (!living(ob[i])) tell_room(SHIP_TO, ob[i]->name() + "��̧���˴���\n", ({ob[i]}));
                                else tell_room(SHIP_TO, ob[i]->name() + "�����˴���\n", ({ob[i]}));
                        }
                }
                message("vision", "������̤�Ű����������ѱ���ʻ���ġ�\n", room);
                room->delete("yell_trigger"); 
        }
}

int do_yell(string arg)
{
        object me = this_player();

        if (!arg) return 0;

        if (arg == "boat") arg = "����";
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���أ�\n");
        if (me->query("age") < 16  )
                message_vision("$Nʹ�����̵���������һ������" + arg + "��\n", me);
        else if (me->query("neili") > 500)
                message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ���˳�ȥ��\n", me);
        else
                message_vision("$N������������Хһ������" + arg + "����\n", me);
        if (arg == "����")
        {
                check_trigger();
                return 1;
        }
        else {
                message_vision("������ԶԶ����һ���������" + arg + "��������\n", me);
                message_vision("��Ȼ��շ���һ�ţ���$N����һ����ͷ��һ���������ȵ������˴���ֹ��������\n", me);
        }
        me->start_busy(1);
        return 1;
}

void reset()
{
        object room;

        ::reset();
        if (room = find_object(__DIR__"duchuan"))
                room->delete("yell_trigger"); 
}

int du_jiang()
{
        object me = this_player();
        object room;
        int cost = 600;
        
        if( !(room = find_object(__DIR__"duchuan")) )
             room = load_object(__DIR__"duchuan");
        if (!living(me)) return 0;
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���أ�\n");
                if(me->query_temp("ride_horse"))
           return notify_fail("���������㲻��ʩչ��һέ�ɽ����ľ��� ��\n");
        if (me->query_skill("dodge") < 270)
                return notify_fail("�����Ϊ������\n");
        if (me->query("max_neili") < 3500)
                return notify_fail("���������Ϊ����������֧�֣���\n");
        if (me->query("neili") < 1000)
                return notify_fail("������������ˣ�\n");
        if (me->query("jingli") < 1200)
                return notify_fail("��ľ��������ˣ�\n");

        if(me->query_encumbrance()/100 > me->query("neili") + cost)
                return notify_fail("�����ô�صİ�������·�������⣬��˵���ˣ�\n");

        if(query("exits/enter")) return notify_fail("�д������������Cool����\n");    
        
        if(!objectp(room = find_object(__DIR__"duchuan") )) return notify_fail("��⣬�����ˣ���֪ͨ��ʦ��\n");
            
        if((int)room->query("yell_trigger")!=1 ) return notify_fail("����̫���ˣ����û����;�����ĵط�����û����Խ��ȥ��\n"); 
        
        me->receive_damage("neili", 300);
        me->receive_damage("jingli", 150);
        tell_room(environment(me), HIC+me->name()+"���˽�������Ʒ�������ų���ƮƮ������Ծ�����׽���\n" NOR, ({me}));
        write("��һ����Ϣ����׼�˽��жɴ�λ�ã�ʹ����һέ�ɽ����Ṧ��Ҫ��Խ���׽���\n");
        me->move(__DIR__"duchuan");
        me->start_busy(3);
        if(me->query_encumbrance()/100 > me->query("neili") + cost
           || me->query("neili") < 700 || me->query("jingli") < 500){
           	write("�㻹��������ȴ�������������ˡ�\n");
           	tell_room(environment(me), HIC+me->name()+"����ƮƮ���ӽ����Ϸ�Ծ������վ�ڴ��ϣ���ڴ�ڴ�������\n" NOR, ({me}));
           	return 1;
           	}
        tell_room(environment(me), HIC+me->name()+"����ƮƮ���ӽ����Ϸ�Ծ�������ڴ���һ�㣬����Ծ����\n" NOR, ({me}));
        write("���ڽ��жɴ�������һ�㣬�����������򱱰���\n");
        me->move(SHIP_TO);
        tell_room(environment(me), HIC"ֻ��"+me->name()+"����ƮƮ�Ӷ԰�Ծ������̬���������ڰ��ߡ�\n"NOR, ({me}));
        me->add("neili", -300);
        me->add("jingli", -150);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( dir =="enter" ){
        if( me->query("can_ride")){
          return 0;
          }       
        if(me->query_temp("ride_horse"))
        return notify_fail("�����ϴ����㲻�´����ˣ�\n");
        }
        return ::valid_leave(me, dir);
}

