// /d/city/xjs.c
// this is made by beyond
// update 1997.7.5
#include <ansi.h>
inherit ROOM;
void create()
{
         set("short",HIW"С��ɽ"NOR);
         set("long",@long
С��ɽԭ��Ϊ�����룬���滷ˮ��ɽ��԰�ֶ��ں��ĵ�С���ϣ�ɽ������
��ͤɽ��ֲ�ɰء�ɽ��´ǽ����С��������֮�����Ļ���һ�������Ļ�����
���ж���һ��������������ˮ������һ��ɽ����
long);
         set("exits",([
         "west" : __DIR__"dhq",
         ]));
	set("outdoors", "����");
         set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}
