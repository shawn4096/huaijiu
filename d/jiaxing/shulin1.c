// /d/jiaxing/shulin1.c ��������

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����ѵ�һ���Ĵ�Ƭ���֣���Χ������һ��, �㼸������·��
LONG
        );

        set("exits", ([
                 "east" : __DIR__"lumu",
                "south" : __DIR__"luzhuang",
                "northwest" : __DIR__"xiaojing1",
        ]));

        set("objects", ([
//     __DIR__"npc/wu-xiuwen" : 1,
        ]));
        set("outdoors", "����");
        set("coor/x",150);
  set("coor/y",-330);
   set("coor/z",0);
   setup();
}

void init()
{   object me = this_player();
    int luck = me->query_temp("oyf_meet");
      if(!me->query("oyf_son") && me->query("oyf_fail") < 4) {
       if(random((int)me->query("kar")) == 5 &&
          me->query_condition("bing_poison") > 30 &&
          me->query("combat_exp") > 100000000){
          if(!luck) {
          write("��ͻȻ���ú��������������ת��ͷ��ȴ����ʲôҲû�С�\n");
          me->set_temp("oyf_meet", 1);
          }   
       if (luck >= 1) {
          write("��ͻȻ���ú��������������ת��ͷ��ȴ����ʲôҲû�С�\n"); 
          me->add_temp("oyf_meet", 1); 
          } 
        }      
     }                         
}
