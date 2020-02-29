#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "Objects/AIZEggRobo.h"
#include "Objects/AIZEncoreTutorial.h"
#include "Objects/AIZKingClaw.h"
#include "Objects/AIZRockPile.h"
#include "Objects/AIZSetup.h"
#include "Objects/AIZTornado.h"
#include "Objects/AIZTornadoPath.h"
#include "Objects/AmoebaDroid.h"
#include "Objects/AnimalHBH.h"
#include "Objects/Announcer.h"
#include "Objects/Aquis.h"
#include "Objects/Armadiloid.h"
#include "Objects/BallCannon.h"
#include "Objects/BallHog.h"
#include "Objects/BarStool.h"
#include "Objects/Batbrain.h"
#include "Objects/Beanstalk.h"
#include "Objects/BGSwitch.h"
#include "Objects/BigSqueeze.h"
#include "Objects/BladePole.h"
#include "Objects/Blaster.h"
#include "Objects/Blastoid.h"
#include "Objects/Bloominator.h"
#include "Objects/BouncePlant.h"
#include "Objects/BreakableWall.h"
#include "Objects/BreakBar.h"
#include "Objects/Bridge.h"
#include "Objects/BSS_Collectable.h"
#include "Objects/BSS_Collected.h"
#include "Objects/BSS_Horizon.h"
#include "Objects/BSS_HUD.h"
#include "Objects/BSS_Message.h"
#include "Objects/BSS_Palette.h"
#include "Objects/BSS_Player.h"
#include "Objects/BSS_Setup.h"
#include "Objects/BuckwildBall.h"
#include "Objects/Buggernaut.h"
#include "Objects/Bumpalo.h"
#include "Objects/Bungee.h"
#include "Objects/BurningLog.h"
#include "Objects/Button.h"
#include "Objects/ButtonDoor.h"
#include "Objects/BuzzBomber.h"
#include "Objects/BuzzSaw.h"
#include "Objects/CableWarp.h"
#include "Objects/Cactula.h"
#include "Objects/Camera.h"
#include "Objects/Canista.h"
#include "Objects/CaterkillerJr.h"
#include "Objects/ChaosEmerald.h"
#include "Objects/CheckerBall.h"
#include "Objects/ChemBubble.h"
#include "Objects/ChemicalBall.h"
#include "Objects/ChemicalPool.h"
#include "Objects/Chopper.h"
#include "Objects/CircleBumper.h"
#include "Objects/Clapperboard.h"
#include "Objects/Clucker.h"
#include "Objects/CollapsingPlatform.h"
#include "Objects/CollapsingSand.h"
#include "Objects/CompetitionMenu.h"
#include "Objects/Constellation.h"
#include "Objects/ContinuePlayer.h"
#include "Objects/ContinueSetup.h"
#include "Objects/ConveyorBelt.h"
#include "Objects/ConveyorPlatform.h"
#include "Objects/ConveyorWheel.h"
#include "Objects/CorkscrewPath.h"
#include "Objects/CPZ1Intro.h"
#include "Objects/CPZ2Outro.h"
#include "Objects/CPZBoss.h"
#include "Objects/CPZSetup.h"
#include "Objects/CPZShutter.h"
#include "Objects/Crabmeat.h"
#include "Objects/Crane.h"
#include "Objects/CrashTest.h"
#include "Objects/Crate.h"
#include "Objects/CreditsSetup.h"
#include "Objects/CrimsonEye.h"
#include "Objects/Current.h"
#include "Objects/CutsceneHBH.h"
#include "Objects/CutsceneSeq.h"
#include "Objects/Cylinder.h"
#include "Objects/DAControl.h"
#include "Objects/Dango.h"
#include "Objects/DASetup.h"
#include "Objects/DashLift.h"
#include "Objects/DBTower.h"
#include "Objects/DCEvent.h"
#include "Objects/DDWrecker.h"
#include "Objects/Debris.h"
#include "Objects/Decoration.h"
#include "Objects/DERobot.h"
#include "Objects/DialogRunner.h"
#include "Objects/DirectorChair.h"
#include "Objects/DiveEggman.h"
#include "Objects/DNARiser.h"
#include "Objects/DoorTrigger.h"
#include "Objects/Dragonfly.h"
#include "Objects/Drillerdroid.h"
#include "Objects/DrillerdroidO.h"
#include "Objects/EggLoco.h"
#include "Objects/Eggman.h"
#include "Objects/EggPistonsMKII.h"
#include "Objects/EggTower.h"
#include "Objects/EggTV.h"
#include "Objects/ElectroMagnet.h"
#include "Objects/EncoreGoodEnd.h"
#include "Objects/EncoreIntro.h"
#include "Objects/ERZGunner.h"
#include "Objects/ERZKing.h"
#include "Objects/ERZMystic.h"
#include "Objects/ERZOutro.h"
#include "Objects/ERZRider.h"
#include "Objects/ERZSetup.h"
#include "Objects/ERZShinobi.h"
#include "Objects/ERZStart.h"
#include "Objects/EscapeCar.h"
#include "Objects/ExtrasMenu.h"
#include "Objects/Fan.h"
#include "Objects/FarPlane.h"
#include "Objects/FBZ1Outro.h"
#include "Objects/FBZ2Outro.h"
#include "Objects/FBZFan.h"
#include "Objects/FBZMissile.h"
#include "Objects/FBZSetup.h"
#include "Objects/FBZSinkTrash.h"
#include "Objects/FBZStorm.h"
#include "Objects/FBZTrash.h"
#include "Objects/FernParallax.h"
#include "Objects/FilmProjector.h"
#include "Objects/FilmReel.h"
#include "Objects/Fireflies.h"
#include "Objects/Firework.h"
#include "Objects/Fireworm.h"
#include "Objects/FlameSpring.h"
#include "Objects/Flamethrower.h"
#include "Objects/FlasherMKII.h"
#include "Objects/FlingRamp.h"
#include "Objects/Flipper.h"
#include "Objects/FlowerPod.h"
#include "Objects/FoldingPlatform.h"
#include "Objects/ForceSpin.h"
#include "Objects/ForceUnstick.h"
#include "Objects/FrostThrower.h"
#include "Objects/Funnel.h"
#include "Objects/FXExpandRing.h"
#include "Objects/FXFade.h"
#include "Objects/FXRuby.h"
#include "Objects/FXSpinRay.h"
#include "Objects/FXTrail.h"
#include "Objects/FXWaveRing.h"
#include "Objects/Gachapandora.h"
#include "Objects/GasPlatform.h"
#include "Objects/GenericTrigger.h"
#include "Objects/GHZ2Outro.h"
#include "Objects/GHZCutsceneK.h"
#include "Objects/GHZCutsceneST.h"
#include "Objects/GHZSetup.h"
#include "Objects/GiantPistol.h"
#include "Objects/GigaMetal.h"
#include "Objects/Gondola.h"
#include "Objects/Grabber.h"
#include "Objects/GreenScreen.h"
#include "Objects/GymBar.h"
#include "Objects/HandLauncher.h"
#include "Objects/HangConveyor.h"
#include "Objects/HangGlider.h"
#include "Objects/HangPoint.h"
#include "Objects/Hatch.h"
#include "Objects/Hatterkiller.h"
#include "Objects/HCZ1Intro.h"
#include "Objects/HCZOneWayDoor.h"
#include "Objects/HCZSetup.h"
#include "Objects/HCZSpikeBall.h"
#include "Objects/HeavyGunner.h"
#include "Objects/HeavyKing.h"
#include "Objects/HeavyMystic.h"
#include "Objects/HeavyRider.h"
#include "Objects/HeavyShinobi.h"
#include "Objects/HiLoSign.h"
#include "Objects/Honkytonk.h"
#include "Objects/Hotaru.h"
#include "Objects/HotaruHiWatt.h"
#include "Objects/HotaruMKII.h"
#include "Objects/HPZEmerald.h"
#include "Objects/Ice.h"
#include "Objects/IceBomba.h"
#include "Objects/IceSpring.h"
#include "Objects/Iwamodoki.h"
#include "Objects/JacobsLadder.h"
#include "Objects/Jawz.h"
#include "Objects/Jellygnite.h"
#include "Objects/JuggleSaw.h"
#include "Objects/JunctionWheel.h"
#include "Objects/Kabasira.h"
#include "Objects/Kanabun.h"
#include "Objects/KingAttack.h"
#include "Objects/KingClaw.h"
#include "Objects/KleptoMobile.h"
#include "Objects/LargeGear.h"
#include "Objects/Launcher.h"
#include "Objects/LaunchSpring.h"
#include "Objects/LaundroMobile.h"
#include "Objects/LavaFall.h"
#include "Objects/LavaGeyser.h"
#include "Objects/LEDPanel.h"
#include "Objects/Letterboard.h"
#include "Objects/LevelSelect.h"
#include "Objects/LightBarrier.h"
#include "Objects/LightBulb.h"
#include "Objects/Localization.h"
#include "Objects/LocoSmoke.h"
#include "Objects/LogoSetup.h"
#include "Objects/LottoBall.h"
#include "Objects/LottoMachine.h"
#include "Objects/LoveTester.h"
#include "Objects/LRZ1Intro.h"
#include "Objects/LRZ1Outro.h"
#include "Objects/LRZ1Setup.h"
#include "Objects/LRZ2Setup.h"
#include "Objects/LRZ3Cutscene.h"
#include "Objects/LRZ3Outro.h"
#include "Objects/LRZ3OutroK.h"
#include "Objects/LRZ3Setup.h"
#include "Objects/LRZConvControl.h"
#include "Objects/LRZConvDropper.h"
#include "Objects/LRZConveyor.h"
#include "Objects/LRZConvItem.h"
#include "Objects/LRZConvSwitch.h"
#include "Objects/LRZFireball.h"
#include "Objects/LRZRockPile.h"
#include "Objects/LRZSpikeBall.h"
#include "Objects/LRZSpiral.h"
#include "Objects/MagnetSphere.h"
#include "Objects/MagPlatform.h"
#include "Objects/MagSpikeBall.h"
#include "Objects/MainMenu.h"
#include "Objects/ManiaModeMenu.h"
#include "Objects/MatryoshkaBom.h"
#include "Objects/MechaBu.h"
#include "Objects/MegaChopper.h"
#include "Objects/MegaOctus.h"
#include "Objects/MenuParam.h"
#include "Objects/MenuSetup.h"
#include "Objects/MetalArm.h"
#include "Objects/MetalSonic.h"
#include "Objects/MeterDroid.h"
#include "Objects/MicDrop.h"
#include "Objects/Mine.h"
#include "Objects/MMZ2Outro.h"
#include "Objects/MMZLightning.h"
#include "Objects/MMZSetup.h"
#include "Objects/MMZWheel.h"
#include "Objects/MonarchBG.h"
#include "Objects/MonarchPlans.h"
#include "Objects/MonkeyDude.h"
#include "Objects/Motobug.h"
#include "Objects/MSBomb.h"
#include "Objects/MSFactory.h"
#include "Objects/MSHologram.h"
#include "Objects/MSOrb.h"
#include "Objects/MSPanel.h"
#include "Objects/MSZ1KIntro.h"
#include "Objects/MSZ2Cutscene.h"
#include "Objects/MSZCutsceneK.h"
#include "Objects/MSZCutsceneST.h"
#include "Objects/MSZSetup.h"
#include "Objects/MSZSpotlight.h"
#include "Objects/Music.h"
#include "Objects/Newspaper.h"
#include "Objects/Newtron.h"
#include "Objects/Octus.h"
#include "Objects/OneWayDoor.h"
#include "Objects/OOZ1Outro.h"
#include "Objects/OOZ2Outro.h"
#include "Objects/OOZFlames.h"
#include "Objects/OOZSetup.h"
#include "Objects/OptionsMenu.h"
#include "Objects/OrbitSpike.h"
#include "Objects/PaintingEyes.h"
#include "Objects/PaperRoller.h"
#include "Objects/ParallaxSprite.h"
#include "Objects/PathInverter.h"
#include "Objects/PauseMenu.h"
#include "Objects/PBL_Bumper.h"
#include "Objects/PBL_Camera.h"
#include "Objects/PBL_Crane.h"
#include "Objects/PBL_Flipper.h"
#include "Objects/PBL_HUD.h"
#include "Objects/PBL_Player.h"
#include "Objects/PBL_Ring.h"
#include "Objects/PBL_Sector.h"
#include "Objects/PBL_Setup.h"
#include "Objects/PBL_TargetBumper.h"
#include "Objects/PetalPile.h"
#include "Objects/PhantomEgg.h"
#include "Objects/PhantomGunner.h"
#include "Objects/PhantomHand.h"
#include "Objects/PhantomKing.h"
#include "Objects/PhantomMissile.h"
#include "Objects/PhantomMystic.h"
#include "Objects/PhantomRider.h"
#include "Objects/PhantomRuby.h"
#include "Objects/PhantomShield.h"
#include "Objects/PhantomShinobi.h"
#include "Objects/PimPom.h"
#include "Objects/Pinata.h"
#include "Objects/Piston.h"
#include "Objects/PKingAttack.h"
#include "Objects/PlaneSeeSaw.h"
#include "Objects/Platform.h"
#include "Objects/PlatformControl.h"
#include "Objects/PlatformNode.h"
#include "Objects/Player.h"
#include "Objects/PlayerProbe.h"
#include "Objects/PohBee.h"
#include "Objects/Pointdexter.h"
#include "Objects/PopcornKernel.h"
#include "Objects/PopcornMachine.h"
#include "Objects/PopOut.h"
#include "Objects/Press.h"
#include "Objects/PrintBlock.h"
#include "Objects/Projectile.h"
#include "Objects/Propeller.h"
#include "Objects/PropellerShaft.h"
#include "Objects/PSZ1Intro.h"
#include "Objects/PSZ1Setup.h"
#include "Objects/PSZ2Intro.h"
#include "Objects/PSZ2Outro.h"
#include "Objects/PSZ2Setup.h"
#include "Objects/PSZDoor.h"
#include "Objects/PSZEggman.h"
#include "Objects/PSZLauncher.h"
#include "Objects/PullChain.h"
#include "Objects/PullSwitch.h"
#include "Objects/PushSpring.h"
#include "Objects/PuyoAI.h"
#include "Objects/PuyoAttack.h"
#include "Objects/PuyoBean.h"
#include "Objects/PuyoGame.h"
#include "Objects/PuyoIndicator.h"
#include "Objects/PuyoLabel.h"
#include "Objects/PuyoLevelSelect.h"
#include "Objects/PuyoMatch.h"
#include "Objects/PuyoScore.h"
#include "Objects/Rattlekiller.h"
#include "Objects/Reagent.h"
#include "Objects/ReplayDB.h"
#include "Objects/ReplayRecorder.h"
#include "Objects/Rexon.h"
#include "Objects/Rhinobot.h"
#include "Objects/RingField.h"
#include "Objects/RisingLava.h"
#include "Objects/RockDrill.h"
#include "Objects/RockemSockem.h"
#include "Objects/RollerMKII.h"
#include "Objects/RotatingSpikes.h"
#include "Objects/RotatingStair.h"
#include "Objects/RPlaneShifter.h"
#include "Objects/RTeleporter.h"
#include "Objects/RubyPortal.h"
#include "Objects/SaveGame.h"
#include "Objects/Scarab.h"
#include "Objects/SchrodingersCapsule.h"
#include "Objects/ScrewMobile.h"
#include "Objects/SDashWheel.h"
#include "Objects/SeeSaw.h"
#include "Objects/SeltzerBottle.h"
#include "Objects/SeltzerWater.h"
#include "Objects/SentryBug.h"
#include "Objects/Shiversaw.h"
#include "Objects/ShopWindow.h"
#include "Objects/Shuriken.h"
#include "Objects/Shutterbug.h"
#include "Objects/SideBarrel.h"
#include "Objects/SilverSonic.h"
#include "Objects/SizeLaser.h"
#include "Objects/SkyTeleporter.h"
#include "Objects/Smog.h"
#include "Objects/Snowflakes.h"
#include "Objects/Sol.h"
#include "Objects/SP500.h"
#include "Objects/SP500MkII.h"
#include "Objects/SparkRail.h"
#include "Objects/Spear.h"
#include "Objects/SpecialClear.h"
#include "Objects/SpeedBooster.h"
#include "Objects/SpiderMobile.h"
#include "Objects/SpikeCorridor.h"
#include "Objects/SpikeCrusher.h"
#include "Objects/SpikeFlail.h"
#include "Objects/SpikeLog.h"
#include "Objects/SpinBooster.h"
#include "Objects/SpinSign.h"
#include "Objects/Spiny.h"
#include "Objects/SpiralPlatform.h"
#include "Objects/Splats.h"
#include "Objects/Springboard.h"
#include "Objects/SPZ1Intro.h"
#include "Objects/SPZ1Setup.h"
#include "Objects/SPZ2Outro.h"
#include "Objects/SPZ2Setup.h"
#include "Objects/SSZ1Intro.h"
#include "Objects/SSZ1Outro.h"
#include "Objects/SSZ1Setup.h"
#include "Objects/SSZ2Setup.h"
#include "Objects/SSZ3Cutscene.h"
#include "Objects/SSZEggman.h"
#include "Objects/SSZSpikeBall.h"
#include "Objects/SSZSpotlight.h"
#include "Objects/Staircase.h"
#include "Objects/Stalactite.h"
#include "Objects/StickyPlatform.h"
#include "Objects/Summary.h"
#include "Objects/SummaryEmerald.h"
#include "Objects/Sweep.h"
#include "Objects/SwingRope.h"
#include "Objects/SwitchDoor.h"
#include "Objects/Syringe.h"
#include "Objects/TAEmerald.h"
#include "Objects/Technosqueek.h"
#include "Objects/TeeterTotter.h"
#include "Objects/TetherBall.h"
#include "Objects/ThanksSetup.h"
#include "Objects/ThoughtBubble.h"
#include "Objects/TilePlatform.h"
#include "Objects/TimeAttackMenu.h"
#include "Objects/TimePost.h"
#include "Objects/TimeTravelSetup.h"
#include "Objects/TippingPlatform.h"
#include "Objects/Title3DSprite.h"
#include "Objects/TitleBG.h"
#include "Objects/TitleEggman.h"
#include "Objects/TitleLogo.h"
#include "Objects/TitleSetup.h"
#include "Objects/TitleSonic.h"
#include "Objects/TMZ1Outro.h"
#include "Objects/TMZ1Setup.h"
#include "Objects/TMZ2Outro.h"
#include "Objects/TMZ2Setup.h"
#include "Objects/TMZ3Setup.h"
#include "Objects/TMZAlert.h"
#include "Objects/TMZBarrier.h"
#include "Objects/TMZCable.h"
#include "Objects/TMZFlames.h"
#include "Objects/Tornado.h"
#include "Objects/TornadoPath.h"
#include "Objects/Toxomister.h"
#include "Objects/TransportTube.h"
#include "Objects/TryAgain.h"
#include "Objects/TryAgainE.h"
#include "Objects/TTCutscene.h"
#include "Objects/TubeSpring.h"
#include "Objects/Tubinaut.h"
#include "Objects/Tuesday.h"
#include "Objects/Turbine.h"
#include "Objects/TurboSpiker.h"
#include "Objects/TurboTurtle.h"
#include "Objects/Turntable.h"
#include "Objects/TurretSwitch.h"
#include "Objects/TVFlyingBattery.h"
#include "Objects/TVPole.h"
#include "Objects/TVVan.h"
#include "Objects/TwistedTubes.h"
#include "Objects/TwistingDoor.h"
#include "Objects/TwistingSlide.h"
#include "Objects/UberCaterkiller.h"
#include "Objects/UFO_Camera.h"
#include "Objects/UFO_Circuit.h"
#include "Objects/UFO_Decoration.h"
#include "Objects/UFO_Dust.h"
#include "Objects/UFO_HUD.h"
#include "Objects/UFO_ItemBox.h"
#include "Objects/UFO_Message.h"
#include "Objects/UFO_Plasma.h"
#include "Objects/UFO_Player.h"
#include "Objects/UFO_Ring.h"
#include "Objects/UFO_Setup.h"
#include "Objects/UFO_Shadow.h"
#include "Objects/UFO_SpeedLines.h"
#include "Objects/UFO_Sphere.h"
#include "Objects/UFO_Springboard.h"
#include "Objects/UFO_Water.h"
#include "Objects/UIBackground.h"
#include "Objects/UIButton.h"
#include "Objects/UIButtonLabel.h"
#include "Objects/UIButtonPrompt.h"
#include "Objects/UICarousel.h"
#include "Objects/UICharButton.h"
#include "Objects/UIChoice.h"
#include "Objects/UIControl.h"
#include "Objects/UICreditsText.h"
#include "Objects/UIDialog.h"
#include "Objects/UIDiorama.h"
#include "Objects/UIHeading.h"
#include "Objects/UIInfoLabel.h"
#include "Objects/UIKeyBinder.h"
#include "Objects/UILeaderboard.h"
#include "Objects/UIMedallionPanel.h"
#include "Objects/UIModeButton.h"
#include "Objects/UIOptionPanel.h"
#include "Objects/UIPicture.h"
#include "Objects/UIPopover.h"
#include "Objects/UIRankButton.h"
#include "Objects/UIReplayCarousel.h"
#include "Objects/UIResPicker.h"
#include "Objects/UISaveSlot.h"
#include "Objects/UIShifter.h"
#include "Objects/UISlider.h"
#include "Objects/UISubHeading.h"
#include "Objects/UITABanner.h"
#include "Objects/UITAZoneModule.h"
#include "Objects/UIText.h"
#include "Objects/UITransition.h"
#include "Objects/UIUsernamePopup.h"
#include "Objects/UIVideo.h"
#include "Objects/UIVsCharSelector.h"
#include "Objects/UIVsResults.h"
#include "Objects/UIVsRoundPicker.h"
#include "Objects/UIVsScoreboard.h"
#include "Objects/UIVsZoneButton.h"
#include "Objects/UIWaitSpinner.h"
#include "Objects/UIWidgets.h"
#include "Objects/UIWinSize.h"
#include "Objects/UncurlPlant.h"
#include "Objects/Valve.h"
#include "Objects/VanishPlatform.h"
#include "Objects/Vultron.h"
#include "Objects/WalkerLegs.h"
#include "Objects/WallBumper.h"
#include "Objects/WarpDoor.h"
#include "Objects/Water.h"
#include "Objects/WaterfallSound.h"
#include "Objects/WaterGush.h"
#include "Objects/WeatherMobile.h"
#include "Objects/WeatherTV.h"
#include "Objects/Whirlpool.h"
#include "Objects/WoodChipper.h"
#include "Objects/Woodrow.h"
#include "Objects/YoyoPulley.h"
#include "Objects/ZipLine.h"
#include "Objects/Zone.h"

#endif //!GAME_OBJECTS_H
