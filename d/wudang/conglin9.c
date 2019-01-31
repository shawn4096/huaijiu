// Room : /d/wudang/conglin9.c ����
// By lius 99/8

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIW"��ѩ����"NOR);
        set("long", @LONG
����Խ��Խ�ߣ�����Խת���䣬·�ϡ����϶��������Ļ�ѩ���н�Խ��
Խ���ѣ���֮Ұ�޵�Ϯ������ֻ���������뿪��Ƭ���֡�
LONG                           
        );

        set("exits", ([               
                 "east" : __DIR__"conglin"+(random(4)+5),
                 "west" : __DIR__"conglin8",
                 "south" : __DIR__"conglin"+(random(4)+5),
                 "north" : __DIR__"conglin"+(random(12)+5),
                 "northeast" : __DIR__"conglin"+(random(12)+5),
                 "northwest" : __DIR__"conglin"+(random(12)+5),
                 "southeast" : __DIR__"conglin10",
                 "southwest" : __DIR__"conglin"+(random(12)+5),
        ]));

	 set("objects", ([
                          __DIR__"npc/xiong" : 1, 
                          __DIR__"npc/bao" : 1,
        ]));

        setup();

}

void init()
{
         add_action("do_zhao", ({"zhao","find"}));
}

int do_zhao(string arg)
{       object yaocai;
        object me;
        int name;        
        me = this_player();
        name = (int)me->query_temp("caiyao_name",1);
        if (me->is_busy())
        return notify_fail ("�����ں�æ��\n");
        if (me->is_fighting())
        return notify_fail ("�㻹��ר��ս���ɡ���\n");        
        if (!( present("yao chu", me)))
        return notify_fail("��������Ѱҩ�ģ�ͻȻ��������ҩ���������������գ���\n");
        if ( !arg || arg != "yaocai" )
        return notify_fail("��Ҫ��ʲô��\n");
        if (!(int)me->query_temp("caiyao_room"))
        return notify_fail("������Щҩ�Ŀ��ǽ�ȱ�쳣����Ͳ�Ҫ��̣�˰ɣ���\n");
        if(((int)me->query_temp("caiyao_room",1) != 9) && (random(5) < 1 ))
        return notify_fail("���Ŀ�Ĺˣ����а��ҩ�ĵ�Ӱ�ӣ����ǵ������ط������ɣ�\n");
        if ( (int)me->query("jingli")<200) 
        return notify_fail ("����ʮ��ƣ������Ҫ�ú���Ϣ�ˣ�\n");        
        if(((int)me->query_temp("caiyao_room",1) == 9 ) && (random(5) < 1 )){
        me->delete_temp("caiyao_room");
        me->set_temp("caiyao_ok",1);
        me->add("jingli",-30);
        message_vision("$N�����ݴԣ�ͻȻ����һ��"YEL+name+NOR",��ϲ��񣬸�æ����ҩ���������������뻳�С�\n",me);
        switch(name) {
          case "����":
               yaocai=new(__DIR__"obj/shengdi");
               yaocai->move(me);
               break;
          case "����":
               yaocai=new(__DIR__"obj/fuling");
               yaocai->move(me);
               break;
          case "�컨":
               yaocai=new(__DIR__"obj/honghua");
               yaocai->move(me);
               break;    
          case "����":
               yaocai=new(__DIR__"obj/lingxian");
               yaocai->move(me);
               break;
          case "����":
               yaocai=new(__DIR__"obj/taoxian");
               yaocai->move(me);
               break;
          case "ûҩ":
               yaocai=new(__DIR__"obj/meiyao");
               yaocai->move(me);
               break;
          case "����֬":
               yaocai=new(__DIR__"obj/wulingzhi");
               yaocai->move(me);
               break;
          case "ǧ����":
               yaocai=new(__DIR__"obj/qianjinzi");
               yaocai->move(me);
               break;
          case "����":
               yaocai=new(__DIR__"obj/danggui");
               yaocai->move(me);
               break;
          case "Զ־":
               yaocai=new(__DIR__"obj/yuanzhi");
               yaocai->move(me);
               break;
          case "����":
               yaocai=new(__DIR__"obj/duhuo");
               yaocai->move(me);
               break;
          case "����":
               yaocai=new(__DIR__"obj/fangfeng");
               yaocai->move(me);
               break;}                  
         return 1;  
        }        
        else
        me->add("jingli",-(100+random(20)));
        message_vision("$N�۹��Ƶ磬Ѹ�ٵ��ڴ�������Ѱ�š�\n", me);
        return 1;
}
int valid_leave(object me, string dir)
{
 if (dir) {
me->start_busy(2);
me->add("jingli",-30);
return 1; }
return ::valid_leave(me,dir);
}
