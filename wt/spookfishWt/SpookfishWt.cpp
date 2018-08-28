#include "SpookfishWt.hpp"

// Private Methods.

void SpookfishApplication::SetVideoPlaybackStatus(const std::string str)
{
  VideoPlaybackStatus->setText(str.c_str());
}

void SpookfishApplication::SetupVideoPlayer()
{
  std::string mp4Video = "https://www.webtoolkit.eu/videos/sintel_trailer.mp4";
  VideoPlayer->addSource(Wt::WLink(mp4Video));
  VideoPlayer->resize(640, 400);

  std::string str("<p>Video playing</p>");
  VideoPlayer->playbackStarted().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video paused</p>";
  VideoPlayer->playbackPaused().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Volume changed</p>";
  VideoPlayer->volumeChanged().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));
  str.clear();
  str = "<p>Video Ended</p>";
  VideoPlayer->ended().connect(boost::bind(&SpookfishApplication::SetVideoPlaybackStatus, this, str));

  VideoPlayerDivVideoWidgetDiv->addWidget(VideoPlayer.get());
  VideoPlayerDiv->addWidget(VideoPlayerDivVideoWidgetDiv.get());
  VideoPlayerDivStatusDiv->addWidget(VideoPlaybackStatus.get());
  VideoPlayerDiv->addWidget(VideoPlayerDivStatusDiv.get());

  VideoPlayerDiv->hide();
}

void SpookfishApplication::SetupTheme()
{
  Theme->setVersion(Wt::WBootstrapTheme::Version3);
  setTheme(Theme.get());

  useStyleSheet(Wt::WLink("styleSheet.css"));
  //useStyleSheet(Wt::WLink("resources/main.css"));
  useStyleSheet(Wt::WLink("resources/themes/bootstrap/3/bootstrap.min.css"));

}

void SpookfishApplication::SetupHeader()
{
  HeaderDiv->setId("header");
  HeaderDiv->setStyleClass(Wt::WString::fromUTF8(""));
  HeaderDivTextDiv->setId("h3");
  HeaderDivTextDiv->addWidget(HeaderText.get());
  HeaderDiv->addWidget(HeaderDivTextDiv.get());
}

void SpookfishApplication::SetupSearchVideoBar()
{
  // To support multi resolution devices need to enable the below line.
  //SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6 col-xs-6 col-lg-6 col-sm-6"));

  SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-6"));
  SearchDiv->setStyleClass(Wt::WString::fromUTF8("input-group"));

  // Expirimenting on the single line of class support. Works but need to test more
  // with different set of options.
  //SearchDiv->setStyleClass(Wt::WString::fromUTF8("col-md-12 input-group"));

  SearchLineEdit->setStyleClass(Wt::WString::fromUTF8("form-control"));
  SearchLineEdit->setFocus(true);
  SearchDivPlayButtonDiv->setStyleClass(Wt::WString::fromUTF8("input-group-btn"));
  PlayButton->setStyleClass(Wt::WString::fromUTF8("btn btn-success with-label"));

  SearchDivLineEditDiv->addWidget(SearchLineEdit.get());
  SearchDivPlayButtonDiv->addWidget(PlayButton.get());

  SearchDiv->addWidget(SearchDivLineEditDiv.get());
  SearchDiv->addWidget(SearchDivPlayButtonDiv.get());

  // Setup signal and slot when user press enter after entering the URL.
  SearchLineEdit->enterPressed().connect
        (boost::bind(&SpookfishApplication::OnPlayButtonPressed, this));
  PlayButton->clicked().connect(this, &SpookfishApplication::OnPlayButtonPressed);

}

void SpookfishApplication::SetupFooter()
{
  FooterDiv->setId("footer");
  FooterDivTextDiv->addWidget(FooterText.get());
  FooterDiv->addWidget(FooterDivTextDiv.get());
}

void SpookfishApplication::OnPlayButtonPressed()
{
  VideoPlayerDiv->show();
}


// Public methods

SpookfishApplication::SpookfishApplication(const WEnvironment& env)
  : WApplication(env),
  Theme(std::make_unique<Wt::WBootstrapTheme>()),
  BodyDiv(std::make_unique<Wt::WContainerWidget>(root())),
  HeaderDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderDivTextDiv(std::make_unique<Wt::WContainerWidget>()),
  HeaderText(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("spookfish"))),
  MainLeftDiv(std::make_unique<Wt::WContainerWidget>()),
  MainRightDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchDivLineEditDiv(std::make_unique<Wt::WContainerWidget>()),
  SearchLineEdit(std::make_unique<Wt::WLineEdit>(Wt::WString::fromUTF8("Give me Youtube URL"))),
  SearchDivPlayButtonDiv(std::make_unique<Wt::WContainerWidget>()),
  PlayButton(std::make_unique<Wt::WPushButton>(Wt::WString::fromUTF8("Play"))),
  VideoPlayerDiv(std::make_unique<Wt::WContainerWidget>()),
  VideoPlayerDivVideoWidgetDiv(std::make_unique<Wt::WContainerWidget>()),
  VideoPlayer(std::make_unique<Wt::WVideo>()),
  VideoPlayerDivStatusDiv(std::make_unique<Wt::WContainerWidget>()),
  VideoPlaybackStatus(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("Playback not started."))),
  FooterDiv(std::make_unique<Wt::WContainerWidget>()),
  FooterDivTextDiv(std::make_unique<Wt::WContainerWidget>()),
  FooterText(std::make_unique<Wt::WText>(Wt::WString::fromUTF8("© Copyrights spookfish. All Rights Reserved.")))
{
  SetupTheme();
  SetupHeader();

  MainLeftDiv->setId("main_left");
  MainRightDiv->setId("main_right");

  SetupSearchVideoBar();
  MainLeftDiv->addWidget(SearchDiv.get());

  SetupVideoPlayer();
  MainLeftDiv->addWidget(VideoPlayerDiv.get());

  SetupFooter();

  // Attach all the containers/divs in the same flow as
  // browser renders the components.
  BodyDiv->addWidget(HeaderDiv.get());
  BodyDiv->addWidget(MainRightDiv.get());
  BodyDiv->addWidget(MainLeftDiv.get());
  BodyDiv->addWidget(FooterDiv.get());
}

SpookfishApplication::~SpookfishApplication()
{
  // Empty
}