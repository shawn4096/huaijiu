// chenglingsu

inherit NPC;
 
string ask_me();
void create()
{
       set_name("程灵素", ({ "cheng lingsu", "cheng" }));
       set("nickname", "药师");
       set("long", 
               "她就是药师程灵素。\n"
               "年纪已仅有二十来岁，但是各种药理极为精通。\n");
        set("gender", "女性");
       set("age", 21);
       set("attitude", "friendly");
       set("shen", -3000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);
       
       set("max_qi", 200);
       set("max_jing", 100);
       set("neili", 1000);
       set("max_neili", 1000);
       set("jiali", 10);
       set("combat_exp", 80000);
 
       set_skill("force", 60);
        set_skill("yinyun-ziqi", 60);
       set_skill("dodge", 60);
       set_skill("jinshe-zhangfa", 60);
       set_skill("tiyunzong", 60);
       set_skill("strike", 60);
       set_skill("jinshe-jianfa", 60);
       set_skill("parry", 60);
       set_skill("sword", 60);
       set_skill("poison", 160);
       set_skill("medicine", 160);
       set_skill("literate", 120);
        map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("strike", "jinshe-zhangfa");
       map_skill("parry", "jinshe-jianfa");
       map_skill("sword", "jinshe-jianfa");
       prepare_skill("strike", "jinshe-zhangfa");

       set("inquiry", ([
              
                "五毒教" : (: ask_me :),
                "禁地" : (: ask_me :),
       ]));
       setup();
       carry_object("/clone/armor/cloth")->wear();
}
void init()
{        
     add_action("do_yes","yes");
     add_action("do_no","no");
}
string ask_me()
{
       object applicant;
       object ob;
       int exp;
       applicant=this_player();

        exp=(int)applicant->query("combat_exp",1); 
        if(exp<90000)
        return "你就这点功夫，恐怕连五毒教的山也上不去，等几年在说吧！\n"; 
 
        if (  present("jiuxuebiyun dan", this_player()) )
        return "我已经给过你了，为何还要向我要？此药很难炼制，不要太贪心！\n";
       
        if( applicant->query("wudu_jiedu") ){
        ob = new(__DIR__"obj/jxdan1");
        ob->move(applicant);
        message_vision("$N获得一颗九雪碧云丹。\n",this_player());
 
        return "你上次答应我的事情还没做，怎麽又来要？ 程灵素皱了皱眉，
冷冷的说到：“丹到还有一颗，你要就拿去吧。\n";
        }
 
         applicant->set_temp("marks/程",1);
         return "五毒教的禁地种满了各种奇花异草，其中大部分具有巨毒，如果一旦随着
空气吸入体中，必将中毒而死。如果你想去五毒教，我这里有颗丹药可抵制其毒。你如能
进去帮我寻得雪蛛，我愿将此药赠于你，你考虑一下，是否答应(yes)或者不答应(no)我。\n";
        
        
}
int do_yes()
{
    
   object jxdan, me, ob;
   me = this_object();
   ob = this_player();

   if(!ob->query_temp("marks/程")) return 0;
        jxdan = new(__DIR__"obj/jxdan");
   ob->set("wudu_jiedu", 1);
   ob->delete_temp("marks/程");	
   jxdan->move(this_player());
   message_vision("$N获得一颗九雪碧云丹。\n",this_player());
   message_vision("$N对你微微一笑，说道：祝你此行顺利。另外希望你能言而有信。\n",me, this_object()); 
   return 1;
} 
int do_no()
{
   object me = this_player();
   if(!me->query_temp("marks/程")) return 0;
   message_vision("程灵素无奈的一笑，说到，既然你不能答应我的要求，丹药自然不能给你。\n",me);
   me->delete_temp("marks/程");	
   
   return 1;
}
int accept_object(object who, object ob,object me)
{
        if (ob->query("id") != "xue zhu" ){
             command("? "+(string)who->query("id"));
             return 0;
             }
       
        command("thank " + who->query("id"));
        command("say 你果然言而有信，下次你要再去五毒教来找我吧。\n");
        call_out("destroying", 1, ob);        
        who->delete("wudu_jiedu");
        return 1;
}
void destroying(object obj)
{
        destruct(obj);
        return;
}
