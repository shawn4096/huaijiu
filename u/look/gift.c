#include <ansi.h>

inherit ITEM;

int launching(object me);
void init()
{
    if(wizardp(this_player()))
       add_action("do_launch", "send");
}

void create()
{
       set_name(GRN"圣水"NOR, ({"holly water", "water"}));
       if (clonep())
               set_default_object(__FILE__);
       else {
               set("value", 1000);
               set("unit", "滴");
               set("no_get", 0);
               set("no_drop", 0);
       }
}

int do_launch()
{
       object *dest;
       int i, j;
       
       j = 0;
       dest = users();
       i = sizeof(dest);
       while(i--)
        if(!dest[i]->query("gift/国庆") && dest[i]->query("registered")
           && dest[i]->query("age") && (int)dest[i]->query("combat_exp")>1000){
                 j = 1;
	         message_vision(HIY "正在给"+dest[i]->query("name")+"发送礼物。\n"NOR,this_object());  
                 launching(dest[i]);
                 break;
         }
             
       if(j < 1){
         message_vision(HIY "好了，已经发完了。\n"NOR,this_object());  
         destruct(this_object());                
         return 1;
         }
       return 1;
}

int launching(object me)
{
          tell_object(me, GRN "一声“" BLINK "热烈祝贺本书剑分站正式开站！" GRN "”，从天上掉下一个大礼包正好砸在你的脚上！\n" NOR);
          new("/u/bbb/bag")->move(me);
          EMOTE_D->do_emote(me,"pain"); 
          me->set("gift/新分站", 1);
          remove_call_out("do_launch");
          call_out("do_launch", 8);
          return 1;
}
