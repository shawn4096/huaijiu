//qi.c 戚芳 by river

#include <ansi.h>
inherit NPC;
 
void create()
{
        set_name("戚芳", ({ "qi fang","qi","fang", "woman" }));        
        set("gender", "女性");
        set("age", 21); 
        set("long", "圆圆的脸蛋，一双大眼黑溜溜的。\n");
        set("combat_exp", 3000);
        set("shen_type", 1);
        set("attitude", "friendly");        

        set_skill("force", 30);
        set_skill("strike", 30);
        set_skill("sword", 30);
	set_skill("shenzhao-jing",30);
        map_skill("force", "shenzhao-jing");         
 
        set("inquiry", 
                ([
                        "万圭" : "他是我的夫君啊。",
		]));

        setup();
        carry_object(ARMOR_D("cloth"))->wear();
        add_money("silver", 3);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{      
       if( !ob || environment(ob) != environment() ) return;
       if ( ob ->query("combat_exp") < 300) {
       command("wanfu "+ob->query("id"));
       command("say  这位" + RANK_D->query_respect(ob) +"来武馆多久啦？在这儿练功之余可和别人闲聊 "HIY HBCYN"chat"CYN"
来交流交流感情。还可以散布些谣言 "HIY HBCYN" rumor"CYN" ,同一门派的还可以用 "HIY HBCYN" party"CYN"。
闲聊和散布谣言时可用些已经有的动作。你可以试试 "HIY HBCYN"chat* hi"CYN" 。用 "HIY HBCYN"semote"CYN"
可以查出哪些是已有了的动作。若你话太多惹人厌就会被人投票关闭交谈频
道。 "HIY HBCYN"vote chblk xxx"CYN" 频道被关了后只有等别人投票打开。 "HIY HBCYN"vote unchblk
xxx"CYN" 如果你想找人聊天而不想让其他人听到，你可以告诉 "HIY HBCYN"tell"CYN" 他(她)。有
人告诉你什么事，你可以用 "HIY HBCYN"reply"CYN" 来回答他（她）。你还可以跟某一位与你
在同一房间的人讲悄悄话 "HIY HBCYN"whisper"CYN" 。江湖上不少人沉迷在武功之中，喜欢打
打杀杀的，然而我觉得还是闲聊交友更有趣。你好自为之吧。"NOR);
	   }
}                               

 


