//�// xiaolu1.c �ּ�С��
#include <ansi.h>

inherit ROOM;
int do_jiao(string arg);

void create()
{
        set("short", "�ּ�С��");
        set("long", @LONG
������һ��С���ϣ��������������ӣ�����ɭɭ���������أ���
����Ҷ��������������������Ķ�����������������ԣ�����һ�곤
������(guoshu)��Ϊ���
LONG
        );

        set("exits", ([
                "west" : __DIR__"liangongfang",
                "southeast" : __DIR__"xilang1",
                "north" : __DIR__"xixiangfang",

        ]));
                 
        set("objects",([
                "/kungfu/class/wudang/fengsong" : 1,
        ]));


        set("item_desc", ([
               "guoshu" : "���������ɽ��ֲ���ɹ����磬��Ϊ���ڷ����ʧȥ������֦Ҷή�ң����ܿ������!\n"
        ]) );

        set("jiao_count", 3);
set("guo_count", 1);

        setup();
}

void init()
{
        add_action("do_jiao", "jiao");

}
int do_jiao(string arg)
{       mapping fam;
        object me;
        object obguo;
        me = this_player();


        if ( !arg || arg != "guoshu" )
                return 0;

        if (!(fam = me->query("family")) || fam["family_name"] != "�䵱��")
               return notify_fail("���뱾�������������ֺα�����������!\n");

    if (! present("xiang cha", this_player()))
        return notify_fail("����ʲô����?!\n");
     
     message_vision(HIG"$Nϸ�ĵذѲ豭���Ů���㽽�ڳ��������ϡ�\n"NOR, me);
     if (present("xiang cha", me))
     destruct(present("xiang cha",me));

     add("jiao_count", -1);
     if (query("jiao_count") > 0) {
        message_vision(HIG"��豻�������գ�֦Ҷ���ø������ˡ�\n"NOR, me);
        return 1;
        }
     if (query("guo_count") >=1)
      {
        add("guo_count", -1);
        write(HIM"ͻȻ�����м䳤��һ�����٣��漴���������Ͼͽ��һ�������������εĳ�����!\n"NOR);
        message_vision("$NС�������ժ�³��������������˵ش��뻳�С�\n",me);
        obguo = new("/clone/medicine/rsg");
        obguo->move(me);
        set("jiao_count", 3);
        return 1;
      }
      else
      {
       set("jiao_count", 3);
       message_vision(HIG"����Ӫ����������������ֻ�ܿ���һ��������С����\n"NOR, me);
      }
        return 1;
}

