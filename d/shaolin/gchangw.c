// Room: /d/shaolin/gchangw.c
// Date: CSWORD 96/02/28

inherit ROOM;

void create()
{
       set("short", "��ǰ�㳡");
       set("long", @LONG
������������ǰ�Ĺ㳡�������㳡�ɴ�����ʯ�̳ɣ���Ϊƽ̹������
�����Զ������Щ���𡣴Դ�С�ݴ�ʯ��ķ�϶�г��˳������㳡��Χ����
���ܵ������֣��Ľ��ϸ����˼���ʯ�����ּ�����Ϊģ������ǰ����������
վ�ż���ɮ�ˡ�
LONG
       );

       set("exits", ([
/*
              "west" : __DIR__"caidi",
*/
               "east" : __DIR__"guangchang1",
       ]));


       set("outdoors", "shaolin");
       set("objects",([
               CLASS_D("shaolin") + "/qing-wei" : 1,
       ]));
       set("coor/x",40);
  set("coor/y",200);
   set("coor/z",110);
   setup();
}
