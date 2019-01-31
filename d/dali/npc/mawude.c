// mawude.c 马五德

#include <ansi.h>
#include <localtime.h>
inherit NPC;

int ask_me1();
int ask_me2();
private void set_enter_date(object ob,int date);
private int query_date(int date);

void create()
{
        set_name("马五德", ({ "ma wude", "ma", "wude" }) );
	set("gender", "男性");         
        set("title", "滇南普洱老武师");
        set("age", 65);
	set("long","马五德是大茶商，豪富好客，颇有孟尝之风。\n");
        set("combat_exp", 200000);
        set("shen_type", 1);
	set("attitude", "peaceful");
        set("unique", 1);

        set("str", 28);
        set("con", 26);
	set("int", 20);
	set("dex", 24);
        set("per", 13);

        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 800);
        set("eff_jingli", 500);
        set("max_neili", 800);
       
        set_skill("force", 80);  
        set_skill("yijin-jing", 80);
        set_skill("sword", 80);
        set_skill("dodge", 80);
        set_skill("strike", 80);
        set_skill("cuff", 80);
        set_skill("weituo-zhang", 80);
        set_skill("parry", 80);
        set_skill("luohan-quan",80);
        set_skill("shaolin-shenfa", 80);
        map_skill("parry", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "luohan-quan");
        map_skill("force","yijin-jing");
        map_skill("strike", "weituo-zhang");
        prepare_skill("strike", "weituo-zhang");
        prepare_skill("cuff", "luohan-quan");

        set("inquiry", ([
                "船队" : (: ask_me1 :),
                "相助" : (: ask_me2 :),

        ]));
        set("chat_chance", 5);
        set("chat_msg", ({
        "马五德面带哀容，道:只剩我一个,此生何趣！。\n",
        "马五德自我埋怨道:都怪我，生出什么移居海外的念头，哎!谁知这船队...\n",
        }) );
	setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_me1()
{
        object ob = this_player();

        command("say 当今朝廷昏庸、奸佞横行、民不聊生，小老儿本打算移居海外。\n"
                "不料，满载人货的船队在海上被强人所掠。钱财本是身外之物，只是这家仇岂能罢休。\n"
                "当下已获知强人所在，不知" + RANK_D->query_respect(ob) + "是否有意相助...\n");

        ob->set_temp("marks/勇闯夺命岛1",1);
     
        return 1;
}

int ask_me2()
{
        object ob = this_player();
        int sysdate;

        if (ob->query("dmd_enter_time")) 
	       set_enter_date(ob,ob->query("dmd_enter_time"));
  
        if(!ob->query_temp("marks/勇闯夺命岛1")) {
               command("say " + RANK_D->query_respect(ob) + "何出此言？\n");
               return 1;
         }
        
        if( ob->query("combat_exp") < 2500000 ) {
	       command("disapp "+(string)ob->query("id"));
	       command("say 夺命岛上强人出没，凶险万分，你还是苦练几年再来吧！\n");
               ob->delete_temp("marks/勇闯夺命岛1",1);
	       return 1;
	  }

	sysdate=query_date(time());
        if( ob->query("dmd_enter_date") && sysdate <= ob->query("dmd_enter_date") && !wizardp(ob)) {
               command("say 您看起来十分疲惫，还是明天再来吧。\n");
               tell_object(ob,HIG"你上次进入勇闯夺命岛副本的时间是"+CHINESE_D->chinese_date(ob->query("dmd_enter_time"),1)+"。\n"NOR);
               return 1;
        }

	  command("touch "+(string)ob->query("id"));
	  command("say 我在佛山码头已雇好一艘快船，" + RANK_D->query_respect(ob) + "直接向船老大报我的名号即可！\n");

        ob->delete_temp("marks/勇闯夺命岛1");
        ob->set_temp("marks/勇闯夺命岛2",1);

        return 1;
      
}

private void set_enter_date(object ob,int date)
{
		mixed *local;
		int y, m, d;
		string dmd_enter_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON]+1;
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          dmd_enter_date=y+"0"+m+"0"+d;
		      else
			        dmd_enter_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          dmd_enter_date=""+y+m+"0"+d;
		      else
			        dmd_enter_date=""+y+m+d;
                  }

		ob->set("dmd_enter_date",dmd_enter_date);

}
private int query_date(int date)
{
		mixed *local;
		int y, m, d;
		string query_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON]+1;
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          query_date=y+"0"+m+"0"+d;
		      else
		              query_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          query_date=""+y+m+"0"+d;
		      else
			        query_date=""+y+m+d;
                  }

		return (int)query_date;

}