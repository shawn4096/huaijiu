// /u/leontt/npc/murong-bo.c  慕容博
// by leontt 1/5/2000

inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_blade();
string ask_armor();
string ask_me();
string ask_me1();
void create()
{
        object weapon,armor;
        set_name("慕容博",({"murong bo","murong","bo"}));
        set("title","姑苏慕容老爷子");
        set("nick","以彼之道 还施彼身");
        set("long", 
              "他就是天下号称以彼之道，还彼之身的姑苏慕容博。\n"
              "他脸上带着不可一世的笑容。\n");
        set("age", 57);
        set("attitude", "friendly");
        set("no_bark",1);
        set("no_quest",1);
        set("shen_type", -1);
        set("str", 40); 
        set("int", 40);
        set("con", 40);
        set("dex", 40); 
        set("per", 27);
        set("max_qi", 10000);
        set("max_jing", 6500);
        set("neili", 14500);
        set("max_neili", 14500);
        set("eff_jingli", 4000);
        set("jiali", 150);
        set("combat_exp", 3400000);
        set("score", 300000);                
        set("chat_chance_combat",5);
        set("chat_msg_combat", ({
                (: perform_action, "blade.daoying" :),
                (: perform_action, "strike.riyue" :),
          }));
        set_skill("xingyi-zhang",300);
        set_skill("strike",300);
        set_skill("finger",300);
        set_skill("dodge",300);
        set_skill("force", 200);
        set_skill("canhe-zhi", 300); 
        set_skill("murong-jianfa",300);       
        set_skill("shenyuan-gong", 220);
        set_skill("yanling-shenfa", 300);
        set_skill("douzhuan-xingyi", 300); 
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("literate", 200);
        set_skill("murong-daofa", 300);
        set_skill("blade",300);
        set_skill("xingyi-jianzhen",200);
        
        map_skill("blade", "murong-daofa");
        map_skill("finger", "canhe-zhi");
        map_skill("force", "shenyuan-gong");
        map_skill("dodge", "yanling-shenfa");
        map_skill("parry", "xingyi-zhang");
        map_skill("sword", "murong-jianfa");
        map_skill("strike", "xingyi-zhang");

        prepare_skill("strike","xingyi-zhang");
        
        create_family("姑苏慕容",1,"弟子");
 
        set("inquiry", 
                ([
                        "name" : "我就是以彼之道，还施彼身的姑苏慕容博。\n",
                        "here" : "这里是少林寺的藏经楼。\n",
                        "rumors" : "我那慕容复儿在武林之中闯出了名头，老爷子我是真高兴呀！\n", 
                        "宝刀" : (: ask_blade :),
                        "绿波香露刀" : (: ask_blade :),
                        "龙袍" : (: ask_armor :),
                        "心愿" : (: ask_me :),
                        "无名老僧" : "他老人家无论武功还是禅宗修为都已到达身不可测的境界,但是最近偶尔也和我提起一些心愿.\n",
                        "经书" : (: ask_me1 :),                    
                ]));
        set_temp("apply/damage", 50);
        set_temp("apply/dodge", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/armor", 40);
        setup();
        if (clonep()){
                weapon = unew(BINGQI_D("blade/lvbo-dao"));
                if(!weapon) weapon=new(BINGQI_D("blade"));
                weapon->move(this_object());
                weapon->wield();
 
                armor=unew("/clone/armor/longpao");
                if( ! armor) armor = new(ARMOR_D("cloth"));
                armor->move(this_object());             
                armor->wear();   
        }
        add_money("gold", 5);
}

void attempt_apprentice(object ob)
{
          object me  = this_player();
 
        string name, new_name;
        name = ob->query("name");
 
        if (present("jiaxin", me))
         {  destruct(present("jiaxin",me)); 

           command("say 好吧，既然" + RANK_D->query_respect(ob) + "有我儿的信件，难为你" + 
                "如此辛苦跑来，我就收下你吧。");
 
           new_name = "慕容" + name[<4..<1];
           ob->set("name", new_name);
           command("say 从今以后你就叫做" + new_name + "，希望你能把慕容功夫发扬光大！");
           command("recruit " + ob->parse_command_id_list()[0]);
           command("chat* 淡淡一笑，谁言 以彼之道 还施彼身 绝迹江湖！");
           command("chat* haha"); 
         }
        else
          command("say 我慕容博岂能随便收徒!");
        return;
           
}

string ask_blade()
{ 
        object blade;
        object me, ob;
        mapping fam;
        me = this_player(); 
        ob = this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
           return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
        if (this_player()->query("combat_exp") < 150000)
           return RANK_D->query_respect(this_player())+"看来功力不够，恐怕不能保住这把宝刀。";
        if ( present("lvboxianglu dao", this_player()))
                return RANK_D->query_respect(this_player()) + 
                "绿波香露刀只有一把，而且就在你身上，真是贪得无厌！";
        if ( present("lvboxianglu dao", this_object()))
           {   command("give lvboxianglu dao to "+this_player()->query("id"));
               blade = unew(BINGQI_D("blade")); 
               if(clonep(blade)){
                 blade->move(this_object());
                 command("wield dao"); 
                 }
        else{
                blade = unew(BINGQI_D("blade"));
                blade->move(this_object());
                command("wield dao"); 
        }
        return "望你能为我慕容做出些惊天地、泣鬼神的壮举，才不负我对你的一片期望，这把绿波香露刀就送给你吧！";
        } 
      return "抱歉，你来晚了，我的绿波香露刀已给别人取走了。";
}


string ask_armor()
{ 
        object armor;
        object me, ob;
        mapping fam;
        me = this_player();
        ob = this_object();

        if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
           return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
        if (this_player()->query("combat_exp") < 150000)
           return RANK_D->query_respect(this_player())+"看来功力不够，恐怕不能保住这见龙袍。";
        if ( present("longpao", this_player()))
                return RANK_D->query_respect(this_player()) + 
                "龙袍只有一件，而且就在你身上，真是贪得无厌！";
        if ( present("longpao", this_object()))
           {   command("give longpao to "+this_player()->query("id"));
               if(clonep(armor)){ 
                 armor = unew(ARMOR_D("cloth")); 
                 armor->move(this_object());
                 command("wear cloth"); 
                 }
        else{
                armor = unew(ARMOR_D("cloth"));
                armor->move(this_object());
                command("wear cloth"); 
        }
        return "望你能为我慕容做出些惊天地、泣鬼神的壮举，才不负我对你的一片期望，这件龙袍就送给你吧！";
        }
      return "抱歉，你来晚了，我的龙袍已给别人取走了。";
}


string ask_me()
{ 
        object me = this_player();
        
       mapping my_fam  = me->query("family");

       if (my_fam["generation"] == 35)
       return RANK_D->query_respect(this_player()) + 
               "都找过回来了,难道没事拿大爷我来消遣!";  
       if (!(my_fam) || my_fam["family_name"] != "少林派" || my_fam["generation"] != 36
             || (string)me->query("class")!="bonze" )
               return RANK_D->query_respect(this_player()) + 
               "此事需我少林武功才智具佳之人,你不知道也罢.";
            if (me->query_temp("sl_wm1"))
            return RANK_D->query_respect(this_player()) + 
               "我不是和你说过了吗?你当我慕容博什麽人?";

            me->set_temp("sl_wm1",1);
       return "听师傅偶尔提到昔年他的师兄天明大师奉方丈重托去寻找一部达摩祖师手写的金刚经,
一去数十载渺无音信,师傅言谈中似乎有挂怀之意,我也出去打探过但是也没什麽消息。";
}

string ask_me1()
{ 
        
      object me = this_player();

          if (!present("fanwen jing", me))
         return RANK_D->query_respect(this_player()) + 
               "身上没有经书,怎和老衲打诳语?";
        command("nod");
        tell_room(me,HIY "慕容博袍袖一摆,"+ me->name()
                + "仿佛腾云驾雾一般飞进了里屋。\n"NOR, ({ me }));  
         write(HIY"你觉得一股内劲轻轻把你托起抛进了里屋。\n"NOR);
         
          me->move("/d/shaolin/liwu");
          return "轻声念道,阿弥陀佛.";
}

int accept_object(object who, object ob,object me)
{
        mapping fam;
        me=this_object();
        who=this_player();
        if (ob->query("id")!="shixi biao" || who->query("djsj"))
         {
           command("say 你给我这个东西干什么?\n");
             return 0;
          } 

        if (!(fam = who->query("family")) 
           || fam["family_name"] != "姑苏慕容"){
                command("angry "+who->query("id"));
                command("say 这东西怎么会到你手里的，老衲让你知道厉害！");
                kill_ob(who);
        return 1;
             }
        call_out("destroying", 1, me, ob);           
        command("hmm");

        command("say 既然你不辞辛苦为老衲取回此物，"+
                      RANK_D->query_respect(this_player()) +"那就让我指点指点你吧。");

        command("say 刀剑双绝是我在少林多年的心得所在。我就传授给"+RANK_D->query_respect(who) +"吧。");

	if(random(15)==1 && who->query_temp("djsj"))
	   {
		   command("hehe "+who->query("id"));
		   tell_object(this_player(),HIY"你听了慕容博的指点，对刀剑双绝的奥妙似乎有些心得。\n\n"NOR);
		   who->set("djsj",1);
		   log_file("quest/djsj", sprintf("%s(%s) 失败%d次学到刀剑双绝绝技。经验：%d。\n", who->name(1),who->query("id"), who->query("djsj_fail"),who->query("combat_exp")) );
	   }
	   else
	   {
		   command("ah "+who->query("id"));
		   tell_object(me,HIY"你听了慕容博的指点，对刀剑双绝的奥妙全然不得要领。\n\n"NOR);
		   command("sigh "+who->query("id"));
		   who->add("djsj_fail",1);   		   
	   }
        who->delete_temp("djsj");
        return 1;

}