//  /d/xueshan/shanlu.c 
inherit ROOM;
 void create()
{
       set("short", "��·");
       set("long", @LONG
����һ�����������С·����Ϊ�Ĵ��Թž��Ǹ���֮�أ����Է�����ȥ��
���ܵ��������������ࡣԶ��������ɽ����Ŀ��ȥ�����������棬Ī�Ǿ�����
���Ķ���ɽ��
LONG);
       set("outdoors", "����");

       set("exits", ([
               "northeast" : __DIR__"tulu2",
                          "south" : "/d/emei/qingshijie",
       ]));

       set("coor/x",-180);
  set("coor/y",-100);
   set("coor/z",0);
   setup(); 
}


