// /u/dubei/miaojiang/mjqj

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIY+"�置�澳"+NOR);
        set("long", @LONG
������ɽ����һƬ�յأ����ܿ��������ʻ���̧ͷ��ȥ���ܿ���һƬƬƮ��
�ĸ��ơ���Զ���м��ò�����������泤������ֲ�
LONG                           
        );
        set("xueteng_count",2);
        
        set("exits", ([
                 "south" : __DIR__"guanmucong14",
                 "west" : __DIR__"shulin",
                 "northeast" : __DIR__"mjqj1",
        ]));
        setup();
}

void init()
{
        add_action("do_wa", ({"wa","dig"}));
        
}
 
int do_wa(string arg)
{ 
        object xueteng;
        object me;
        me = this_player();
        if (!( present("xiao tiechan", this_player())))
        return notify_fail("���ڵ��������� ���������С���\n");
        if ( !arg || arg != "xue teng" )
            return notify_fail("����ʲ�᣿\n");
        
          if ( (int)me->query("jingli")<200) 
             { write("��̫���ˣ�\n");
         return 1;
            }
        if(random(20)!=3) {
        me->add("jingli",-120);
        return notify_fail("�����˰��죬ֻ����һЩҰ�ݡ�\n"); 
         }
 
           if (query("xueteng_count") > 0) 
       {
        message_vision("$N��Ȼ����һ���ɫ��Сֲ��Ͽ����������\n",me);
        add("xueteng_count", -1);
        xueteng=new("/clone/medicine/xueteng");
        xueteng->move(me);
        me->add("jingli", -200);
        
        }
        else
       message_vision("$N���˰��죬һ������\n", me);
        return 1;
}
int count = 1;
void reset()
{
    if (--count == 0) {count = 12; set("xueteng_count", 2); ::reset();}
}
int clean_up()
{
       return 0;

}
