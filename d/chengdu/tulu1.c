//  /d/xueshan/shanlu.c 
inherit ROOM;
 void create()
{
       set("short", "土路");
       set("long", @LONG
这是一条尘土飞扬的小路，因为四川自古就是富庶之地，所以放眼望去，
四周的田垅里郁郁青青。远处有座大山，凝目望去但见秀丽雄奇，莫非就是有
名的峨嵋山吗？
LONG);
       set("outdoors", "峨嵋");

       set("exits", ([
               "northeast" : __DIR__"tulu2",
                          "south" : "/d/emei/qingshijie",
       ]));

       set("coor/x",-180);
  set("coor/y",-100);
   set("coor/z",0);
   setup(); 
}


