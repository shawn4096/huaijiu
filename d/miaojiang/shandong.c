// /u/dubei/miaojiang
// by dubei

inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
�������ܺ�����ģ����ֲ�����ָ������ԼԼ�Ŀ����ı������������١�
���ϵ�·��ߵͲ�ƽ�������������⡣
LONG
        );

        set("exits", ([
              "out" : __DIR__"slu9",
               
             ]));
      
 
        set("outdoors", "miaojiang");
        setup();
}

void reset()
{
        if (!random(2)) set("xuezhu_count", 1);
}

void init()
{
        add_action("do_dian", "dian");
        add_action("do_yao", ({ "zuan", "yao" }));
} 
int do_dian(string arg)
{ 
         object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(
             "\n���ȼ�˻��ۣ����Ź����㿴�������ı�ȫ�����٣����� 
�Ŀ�϶�в�����ѩ�׵�֩������\n"
             );
            me->set_temp("mark/��", 1);
             return 1;
         }
}
int do_yao(string arg)
{
        object me;
        me = this_player();
        if ( !arg || arg != "shuteng" )
        return notify_fail("��Ҫ��ʲ�᣿\n");
        if (!me->query_temp("mark/��"))
        return notify_fail("��Ҫ��ʲ�᣿\n");
           if (query("xuezhu_count") > 0) 
          {
           message_vision("$N����ҡ�����٣���Ȼ����һֻѩ�롣\n", me);
           add("xuezhu_count", -1);
           new(__DIR__"npc/xuezhu")->move(__DIR__"shandong",);
           me->delete_temp("mark/��");
          }
        else
           message_vision("$N�ζ��˰��죬����ʲ��Ҳû�С�\n", me);
     return 1;
}
