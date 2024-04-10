actool_verbose = $(actool_verbose_$(V))
actool_verbose_ = $(actool_verbose__$(AM_DEFAULT_VERBOSITY))
actool_verbose_0 = @echo "  ACTOOL  " $@;
actool_verbose__0 = $(actool_verbose_0)

<<<<<<< master
# All content of the asset catalog should be listed below
# so that it is properly rebuilt when its content changes.
ASSET_CATALOG_DEPS = \
	gui/macosx/Resources/Assets.xcassets/Contents.json \
	gui/macosx/Resources/Assets.xcassets/VLCAccentColor.colorset/Contents.json

gui/macosx/Resources/Assets.car: gui/macosx/Resources/Assets.xcassets $(ASSET_CATALOG_DEPS)
	$(AM_V_at)$(MKDIR_P) "gui/macosx/Resources"
	$(actool_verbose)$(ACTOOL) --errors --warnings --notices \
	  --platform macosx --target-device mac --skip-app-store-deployment \
	  --minimum-deployment-target 10.11 --output-format human-readable-text \
	  --compile $(@D) $<

if ENABLE_MACOSX_UI
BUILT_SOURCES += gui/macosx/Resources/Assets.car
endif

EXTRA_DIST += $(ASSET_CATALOG_DEPS)

SUFFIXES += .xib .nib

xib_verbose = $(xib_verbose_$(V))
xib_verbose_ = $(xib_verbose__$(AM_DEFAULT_VERBOSITY))
xib_verbose_0 = @echo "  XIB     " $@;
xib_verbose__0 = $(xib_verbose_0)

.xib.nib:
	$(AM_V_at)mkdir -p -- gui/macosx/UI
	$(xib_verbose)$(XIB) --errors --warnings --notices \
	  --module VLC --auto-activate-custom-fonts --target-device mac \
	  --minimum-deployment-target 10.11 --output-format human-readable-text \
	  --compile $@ $<


libmacosx_plugin_la_OBJCFLAGS = $(AM_OBJCFLAGS) -fobjc-exceptions -fobjc-arc -I$(srcdir)/gui/macosx
libmacosx_plugin_la_LDFLAGS = $(AM_LDFLAGS) -rpath '$(guidir)' \
	-Wl,-framework,AVFoundation \
	-Wl,-framework,Cocoa \
	-Wl,-framework,CoreAudio \
	-Wl,-framework,CoreVideo \
	-Wl,-framework,IOKit \
	-Wl,-framework,QuartzCore \
	-Wl,-framework,ScriptingBridge \
	-Wl,-framework,WebKit \
	-Wl,-framework,QuickLook \
	-Wl,-weak_framework,MediaPlayer
=======
libmacosx_plugin_la_OBJCFLAGS = $(AM_OBJCFLAGS) -fobjc-exceptions -fobjc-arc
libmacosx_plugin_la_LDFLAGS = $(AM_LDFLAGS) -rpath '$(guidir)' \
	-Wl,-framework,Cocoa -Wl,-framework,CoreServices \
	-Wl,-framework,AVFoundation -Wl,-framework,CoreMedia -Wl,-framework,IOKit \
	-Wl,-framework,AddressBook -Wl,-framework,WebKit -Wl,-framework,CoreAudio \
	-Wl,-framework,SystemConfiguration -Wl,-framework,ScriptingBridge \
	-Wl,-framework,QuartzCore -Wl,-weak_framework,MediaPlayer
>>>>>>> origin/3.0.x

if HAVE_SPARKLE
libmacosx_plugin_la_LDFLAGS += -Wl,-framework,Sparkle
endif

libmacosx_plugin_la_SOURCES = \
<<<<<<< master
	gui/macosx/coreinteraction/VLCHotkeysController.h \
	gui/macosx/coreinteraction/VLCHotkeysController.m \
	gui/macosx/coreinteraction/VLCVideoFilterHelper.h \
	gui/macosx/coreinteraction/VLCVideoFilterHelper.m \
	gui/macosx/extensions/NSGradient+VLCAdditions.h \
	gui/macosx/extensions/NSGradient+VLCAdditions.m \
	gui/macosx/extensions/NSColor+VLCAdditions.h \
	gui/macosx/extensions/NSColor+VLCAdditions.m \
	gui/macosx/extensions/NSFont+VLCAdditions.h \
	gui/macosx/extensions/NSFont+VLCAdditions.m \
	gui/macosx/extensions/NSImage+VLCAdditions.h \
	gui/macosx/extensions/NSImage+VLCAdditions.m \
	gui/macosx/extensions/NSMenu+VLCAdditions.h \
	gui/macosx/extensions/NSMenu+VLCAdditions.m \
	gui/macosx/extensions/NSScreen+VLCAdditions.h \
	gui/macosx/extensions/NSScreen+VLCAdditions.m \
	gui/macosx/extensions/NSString+Helpers.h \
	gui/macosx/extensions/NSString+Helpers.m \
	gui/macosx/extensions/NSView+VLCAdditions.h \
	gui/macosx/extensions/NSView+VLCAdditions.m \
	gui/macosx/extensions/VLCHexNumberFormatter.h \
	gui/macosx/extensions/VLCHexNumberFormatter.m \
	gui/macosx/extensions/VLCPositionFormatter.h \
	gui/macosx/extensions/VLCPositionFormatter.m \
	gui/macosx/imported/AppleRemote/AppleRemote.h \
	gui/macosx/imported/AppleRemote/AppleRemote.m \
	gui/macosx/imported/SPMediaKeyTap/SPMediaKeyTap.h \
	gui/macosx/imported/SPMediaKeyTap/SPMediaKeyTap.m \
	gui/macosx/library/VLCInputItem.h \
	gui/macosx/library/VLCInputItem.m \
	gui/macosx/library/VLCInputNodePathControl.h \
	gui/macosx/library/VLCInputNodePathControl.m \
	gui/macosx/library/VLCInputNodePathControlItem.h \
	gui/macosx/library/VLCInputNodePathControlItem.m \
	gui/macosx/library/VLCLibraryCollectionViewDataSource.h \
	gui/macosx/library/VLCLibraryCollectionViewDelegate.h \
	gui/macosx/library/VLCLibraryCollectionViewDelegate.m \
	gui/macosx/library/VLCLibraryCollectionViewFlowLayout.h \
	gui/macosx/library/VLCLibraryCollectionViewFlowLayout.m \
	gui/macosx/library/VLCLibraryCollectionViewItem.h \
	gui/macosx/library/VLCLibraryCollectionViewItem.m \
	gui/macosx/library/VLCLibraryCollectionViewMediaItemSupplementaryDetailView.h \
	gui/macosx/library/VLCLibraryCollectionViewMediaItemSupplementaryDetailView.m \
	gui/macosx/library/VLCLibraryCollectionViewSupplementaryDetailView.h \
	gui/macosx/library/VLCLibraryCollectionViewSupplementaryDetailView.m \
	gui/macosx/library/VLCLibraryCollectionViewSupplementaryElementView.h \
	gui/macosx/library/VLCLibraryCollectionViewSupplementaryElementView.m \
	gui/macosx/library/VLCLibraryController.h \
	gui/macosx/library/VLCLibraryController.m \
	gui/macosx/library/VLCLibraryDataTypes.h \
	gui/macosx/library/VLCLibraryDataTypes.m \
	gui/macosx/library/VLCLibraryImageCache.h \
	gui/macosx/library/VLCLibraryImageCache.m \
	gui/macosx/library/VLCLibraryInformationPanel.h \
	gui/macosx/library/VLCLibraryInformationPanel.m \
	gui/macosx/library/VLCLibraryMenuController.h \
	gui/macosx/library/VLCLibraryMenuController.m \
	gui/macosx/library/VLCLibraryModel.h \
	gui/macosx/library/VLCLibraryModel.m \
	gui/macosx/library/VLCLibraryNavigationStack.h \
	gui/macosx/library/VLCLibraryNavigationStack.m \
	gui/macosx/library/VLCLibraryNavigationState.h \
	gui/macosx/library/VLCLibraryNavigationState.m \
	gui/macosx/library/VLCLibrarySortingMenuController.h \
	gui/macosx/library/VLCLibrarySortingMenuController.m \
	gui/macosx/library/VLCLibraryTableView.h \
	gui/macosx/library/VLCLibraryTableView.m \
	gui/macosx/library/VLCLibraryTableCellView.h \
	gui/macosx/library/VLCLibraryTableCellView.m \
	gui/macosx/library/VLCLibraryUIUnits.h \
	gui/macosx/library/VLCLibraryUIUnits.m \
	gui/macosx/library/VLCLibraryWindow.h \
	gui/macosx/library/VLCLibraryWindow.m \
	gui/macosx/library/VLCLibraryWindowController.h \
	gui/macosx/library/VLCLibraryWindowController.m \
	gui/macosx/library/video-library/VLCLibraryVideoViewController.h \
	gui/macosx/library/video-library/VLCLibraryVideoViewController.m \
	gui/macosx/library/video-library/VLCLibraryVideoCollectionViewsStackViewController.h \
	gui/macosx/library/video-library/VLCLibraryVideoCollectionViewsStackViewController.m \
	gui/macosx/library/video-library/VLCLibraryVideoCollectionViewContainerView.h \
	gui/macosx/library/video-library/VLCLibraryVideoCollectionViewContainerView.m \
	gui/macosx/library/video-library/VLCLibraryVideoCollectionViewContainerViewDataSource.h \
	gui/macosx/library/video-library/VLCLibraryVideoCollectionViewContainerViewDataSource.m \
	gui/macosx/library/video-library/VLCLibraryVideoGroupDescriptor.h \
	gui/macosx/library/video-library/VLCLibraryVideoGroupDescriptor.m \
	gui/macosx/library/video-library/VLCLibraryVideoTableViewDataSource.h \
	gui/macosx/library/video-library/VLCLibraryVideoTableViewDataSource.m \
	gui/macosx/library/audio-library/VLCLibraryAlbumTableCellView.h \
	gui/macosx/library/audio-library/VLCLibraryAlbumTableCellView.m \
	gui/macosx/library/audio-library/VLCLibraryAlbumTracksDataSource.h \
	gui/macosx/library/audio-library/VLCLibraryAlbumTracksDataSource.m \
	gui/macosx/library/audio-library/VLCLibraryAudioDataSource.h \
	gui/macosx/library/audio-library/VLCLibraryAudioDataSource.m \
	gui/macosx/library/audio-library/VLCLibraryAudioGroupDataSource.h \
	gui/macosx/library/audio-library/VLCLibraryAudioGroupDataSource.m \
	gui/macosx/library/audio-library/VLCLibraryAudioViewController.h \
	gui/macosx/library/audio-library/VLCLibraryAudioViewController.m \
	gui/macosx/library/audio-library/VLCLibraryCollectionViewAlbumSupplementaryDetailView.h \
	gui/macosx/library/audio-library/VLCLibraryCollectionViewAlbumSupplementaryDetailView.m \
	gui/macosx/library/audio-library/VLCLibraryCollectionViewAudioGroupSupplementaryDetailView.h \
	gui/macosx/library/audio-library/VLCLibraryCollectionViewAudioGroupSupplementaryDetailView.m \
	gui/macosx/library/audio-library/VLCLibrarySongTableCellView.h \
	gui/macosx/library/audio-library/VLCLibrarySongTableCellView.m \
	gui/macosx/library/audio-library/VLCLibrarySongsTableViewSongPlayingTableCellView.h \
	gui/macosx/library/audio-library/VLCLibrarySongsTableViewSongPlayingTableCellView.m \
	gui/macosx/library/media-source/VLCLibraryMediaSourceViewController.h \
	gui/macosx/library/media-source/VLCLibraryMediaSourceViewController.m \
	gui/macosx/library/media-source/VLCMediaSource.h \
	gui/macosx/library/media-source/VLCMediaSource.m \
	gui/macosx/library/media-source/VLCMediaSourceBaseDataSource.h \
	gui/macosx/library/media-source/VLCMediaSourceBaseDataSource.m \
	gui/macosx/library/media-source/VLCMediaSourceCollectionViewItem.h \
	gui/macosx/library/media-source/VLCMediaSourceCollectionViewItem.m \
	gui/macosx/library/media-source/VLCMediaSourceDataSource.h \
	gui/macosx/library/media-source/VLCMediaSourceDataSource.m \
	gui/macosx/library/media-source/VLCMediaSourceDeviceCollectionViewItem.h \
	gui/macosx/library/media-source/VLCMediaSourceDeviceCollectionViewItem.m \
	gui/macosx/library/media-source/VLCMediaSourceProvider.h \
	gui/macosx/library/media-source/VLCMediaSourceProvider.m \
	gui/macosx/main/CompatibilityFixes.h \
	gui/macosx/main/CompatibilityFixes.m \
	gui/macosx/main/VLCApplication.h \
	gui/macosx/main/VLCApplication.m \
	gui/macosx/main/VLCMain+OldPrefs.h \
	gui/macosx/main/VLCMain+OldPrefs.m \
	gui/macosx/main/VLCMain.h \
	gui/macosx/main/VLCMain.m \
	gui/macosx/main/macosx.m \
	gui/macosx/menus/VLCMainMenu.h \
	gui/macosx/menus/VLCMainMenu.m \
	gui/macosx/menus/VLCStatusBarIcon.h \
	gui/macosx/menus/VLCStatusBarIcon.m \
	gui/macosx/menus/renderers/VLCRendererDiscovery.h \
	gui/macosx/menus/renderers/VLCRendererDiscovery.m \
	gui/macosx/menus/renderers/VLCRendererItem.h \
	gui/macosx/menus/renderers/VLCRendererItem.m \
	gui/macosx/menus/renderers/VLCRendererMenuController.h \
	gui/macosx/menus/renderers/VLCRendererMenuController.m \
	gui/macosx/os-integration/Spotify.h \
	gui/macosx/os-integration/VLCClickerManager.h \
	gui/macosx/os-integration/VLCClickerManager.m \
	gui/macosx/os-integration/VLCSystemVolume.h \
	gui/macosx/os-integration/VLCSystemVolume.m \
	gui/macosx/os-integration/VLCDocumentController.h \
	gui/macosx/os-integration/VLCDocumentController.m \
	gui/macosx/os-integration/VLCKeyboardBacklightControl.h \
	gui/macosx/os-integration/VLCKeyboardBacklightControl.m \
	gui/macosx/os-integration/VLCRemoteControlService.h \
	gui/macosx/os-integration/VLCRemoteControlService.m \
	gui/macosx/os-integration/applescript.h \
	gui/macosx/os-integration/applescript.m \
	gui/macosx/os-integration/iTunes.h \
	gui/macosx/panels/VLCAudioEffectsWindowController.h \
	gui/macosx/panels/VLCAudioEffectsWindowController.m \
	gui/macosx/panels/VLCBookmarksWindowController.h \
	gui/macosx/panels/VLCBookmarksWindowController.m \
	gui/macosx/panels/VLCInformationWindowController.h \
	gui/macosx/panels/VLCInformationWindowController.m \
	gui/macosx/panels/VLCTimeSelectionPanelController.h \
	gui/macosx/panels/VLCTimeSelectionPanelController.m \
	gui/macosx/panels/VLCTrackSynchronizationWindowController.h \
	gui/macosx/panels/VLCTrackSynchronizationWindowController.m \
	gui/macosx/panels/VLCVideoEffectsWindowController.h \
	gui/macosx/panels/VLCVideoEffectsWindowController.m \
	gui/macosx/panels/dialogs/VLCCoreDialogProvider.h \
	gui/macosx/panels/dialogs/VLCCoreDialogProvider.m \
	gui/macosx/panels/dialogs/VLCCustomCropArWindowController.h \
	gui/macosx/panels/dialogs/VLCCustomCropArWindowController.m \
	gui/macosx/panels/dialogs/VLCPopupPanelController.h \
	gui/macosx/panels/dialogs/VLCPopupPanelController.m \
	gui/macosx/panels/dialogs/VLCResumeDialogController.h \
	gui/macosx/panels/dialogs/VLCResumeDialogController.m \
	gui/macosx/panels/dialogs/VLCTextfieldPanelController.h \
	gui/macosx/panels/dialogs/VLCTextfieldPanelController.m \
	gui/macosx/playlist/VLCPlaybackContinuityController.h \
	gui/macosx/playlist/VLCPlaybackContinuityController.m \
	gui/macosx/playlist/VLCPlayerController.h \
	gui/macosx/playlist/VLCPlayerController.m \
	gui/macosx/playlist/VLCPlaylistController.h \
	gui/macosx/playlist/VLCPlaylistController.m \
	gui/macosx/playlist/VLCPlaylistDataSource.h \
	gui/macosx/playlist/VLCPlaylistDataSource.m \
	gui/macosx/playlist/VLCPlaylistItem.h \
	gui/macosx/playlist/VLCPlaylistItem.m \
	gui/macosx/playlist/VLCPlaylistMenuController.h \
	gui/macosx/playlist/VLCPlaylistMenuController.m \
	gui/macosx/playlist/VLCPlaylistModel.h \
	gui/macosx/playlist/VLCPlaylistModel.m \
	gui/macosx/playlist/VLCPlaylistSortingMenuController.h \
	gui/macosx/playlist/VLCPlaylistSortingMenuController.m \
	gui/macosx/playlist/VLCPlaylistTableCellView.h \
	gui/macosx/playlist/VLCPlaylistTableCellView.m \
	gui/macosx/playlist/VLCPlaylistTableView.h \
	gui/macosx/playlist/VLCPlaylistTableView.m \
	gui/macosx/preferences/VLCHotkeyChangeWindow.h \
	gui/macosx/preferences/VLCHotkeyChangeWindow.m \
	gui/macosx/preferences/VLCSimplePrefsController.h \
	gui/macosx/preferences/VLCSimplePrefsController.m \
	gui/macosx/preferences/VLCSimplePrefsWindow.h \
	gui/macosx/preferences/VLCSimplePrefsWindow.m \
	gui/macosx/preferences/prefs.h \
	gui/macosx/preferences/prefs.m \
	gui/macosx/preferences/prefs_widgets.h \
	gui/macosx/preferences/prefs_widgets.m \
	gui/macosx/views/VLCBasicView.h \
	gui/macosx/views/VLCBasicView.m \
	gui/macosx/views/VLCBottomBarView.h \
	gui/macosx/views/VLCBottomBarView.m \
	gui/macosx/views/VLCCustomWindowButton.h \
	gui/macosx/views/VLCCustomWindowButton.m \
	gui/macosx/views/VLCDefaultValueSlider.h \
	gui/macosx/views/VLCDefaultValueSlider.m \
	gui/macosx/views/VLCDefaultValueSliderCell.h \
	gui/macosx/views/VLCDefaultValueSliderCell.m \
	gui/macosx/views/VLCDragDropView.h \
	gui/macosx/views/VLCDragDropView.m \
	gui/macosx/views/VLCHUDOutlineView.h \
	gui/macosx/views/VLCHUDOutlineView.m \
	gui/macosx/views/VLCHUDTableCornerView.h \
	gui/macosx/views/VLCHUDTableCornerView.m \
	gui/macosx/views/VLCHUDTableView.h \
	gui/macosx/views/VLCHUDTableView.m \
	gui/macosx/views/VLCImageButton.h \
	gui/macosx/views/VLCImageButton.m \
	gui/macosx/views/VLCImageView.h \
	gui/macosx/views/VLCImageView.m \
	gui/macosx/views/VLCLinearProgressIndicator.h \
	gui/macosx/views/VLCLinearProgressIndicator.m \
	gui/macosx/views/VLCRoundedCornerTextField.h \
	gui/macosx/views/VLCRoundedCornerTextField.m \
	gui/macosx/views/VLCScrollingClipView.h \
	gui/macosx/views/VLCScrollingClipView.m \
	gui/macosx/views/VLCSlider.h \
	gui/macosx/views/VLCSlider.m \
	gui/macosx/views/VLCSliderCell.h \
	gui/macosx/views/VLCSliderCell.m \
	gui/macosx/views/VLCSubScrollView.h \
	gui/macosx/views/VLCSubScrollView.m \
	gui/macosx/views/VLCTimeField.h \
	gui/macosx/views/VLCTimeField.m \
	gui/macosx/views/VLCTrackingView.h \
	gui/macosx/views/VLCTrackingView.m \
	gui/macosx/views/VLCVolumeSlider.h \
	gui/macosx/views/VLCVolumeSlider.m \
	gui/macosx/views/VLCVolumeSliderCell.h \
	gui/macosx/views/VLCVolumeSliderCell.m \
	gui/macosx/views/VLCWrappableTextField.h \
	gui/macosx/views/VLCWrappableTextField.m \
	gui/macosx/windows/VLCAboutWindowController.h \
	gui/macosx/windows/VLCAboutWindowController.m \
	gui/macosx/windows/VLCDetachedAudioWindow.h \
	gui/macosx/windows/VLCDetachedAudioWindow.m \
	gui/macosx/windows/VLCErrorWindowController.h \
	gui/macosx/windows/VLCErrorWindowController.m \
	gui/macosx/windows/VLCHelpWindowController.h \
	gui/macosx/windows/VLCHelpWindowController.m \
	gui/macosx/windows/VLCOpenInputMetadata.h \
	gui/macosx/windows/VLCOpenInputMetadata.m \
	gui/macosx/windows/VLCOpenWindowController.h \
	gui/macosx/windows/VLCOpenWindowController.m \
	gui/macosx/windows/addons/VLCAddonListItem.h \
	gui/macosx/windows/addons/VLCAddonListItem.m \
	gui/macosx/windows/addons/VLCAddonsWindowController.h \
	gui/macosx/windows/addons/VLCAddonsWindowController.m \
	gui/macosx/windows/convertandsave/VLCConvertAndSaveWindowController.h \
	gui/macosx/windows/convertandsave/VLCConvertAndSaveWindowController.m \
	gui/macosx/windows/convertandsave/VLCOutput.h \
	gui/macosx/windows/convertandsave/VLCOutput.m \
	gui/macosx/windows/extensions/VLCExtensionsDialogProvider.h \
	gui/macosx/windows/extensions/VLCExtensionsDialogProvider.m \
	gui/macosx/windows/extensions/VLCExtensionsManager.h \
	gui/macosx/windows/extensions/VLCExtensionsManager.m \
	gui/macosx/windows/extensions/VLCUIWidgets.h \
	gui/macosx/windows/extensions/VLCUIWidgets.m \
	gui/macosx/windows/logging/VLCLogMessage.h \
	gui/macosx/windows/logging/VLCLogMessage.m \
	gui/macosx/windows/logging/VLCLogWindowController.h \
	gui/macosx/windows/logging/VLCLogWindowController.m \
	gui/macosx/windows/mainwindow/VLCControlsBarCommon.h \
	gui/macosx/windows/mainwindow/VLCControlsBarCommon.m \
	gui/macosx/windows/mainwindow/VLCMainWindowControlsBar.h \
	gui/macosx/windows/mainwindow/VLCMainWindowControlsBar.m \
	gui/macosx/windows/video/VLCAspectRatioRetainingVideoWindow.h \
	gui/macosx/windows/video/VLCAspectRatioRetainingVideoWindow.m \
	gui/macosx/windows/video/VLCFullVideoViewWindow.h \
	gui/macosx/windows/video/VLCFullVideoViewWindow.m \
	gui/macosx/windows/video/VLCMainVideoViewController.h \
	gui/macosx/windows/video/VLCMainVideoViewController.m \
	gui/macosx/windows/video/VLCMainVideoViewOverlayView.h \
	gui/macosx/windows/video/VLCMainVideoViewOverlayView.m \
	gui/macosx/windows/video/VLCVideoOutputProvider.h \
	gui/macosx/windows/video/VLCVideoOutputProvider.m \
	gui/macosx/windows/video/VLCVideoWindowCommon.h \
	gui/macosx/windows/video/VLCVideoWindowCommon.m \
	gui/macosx/windows/video/VLCVoutView.h \
	gui/macosx/windows/video/VLCVoutView.m \
	gui/macosx/windows/video/VLCWindow.h \
	gui/macosx/windows/video/VLCWindow.m
=======
	gui/macosx/helpers.h \
	gui/macosx/VLCAboutWindowController.h gui/macosx/VLCAboutWindowController.m \
	gui/macosx/VLCAddonListItem.h gui/macosx/VLCAddonListItem.m \
	gui/macosx/VLCAddonsWindowController.h gui/macosx/VLCAddonsWindowController.m \
	gui/macosx/applescript.h gui/macosx/applescript.m \
	gui/macosx/AppleRemote.h gui/macosx/AppleRemote.m \
	gui/macosx/CompatibilityFixes.h gui/macosx/CompatibilityFixes.m \
	gui/macosx/VLCControlsBarCommon.m gui/macosx/VLCControlsBarCommon.h \
	gui/macosx/VLCDocumentController.m gui/macosx/VLCDocumentController.h \
	gui/macosx/VLCMainWindowControlsBar.m gui/macosx/VLCMainWindowControlsBar.h \
	gui/macosx/VLCConvertAndSaveWindowController.h gui/macosx/VLCConvertAndSaveWindowController.m \
	gui/macosx/VLCCoreInteraction.h gui/macosx/VLCCoreInteraction.m \
	gui/macosx/VLCErrorWindowController.h gui/macosx/VLCErrorWindowController.m \
	gui/macosx/VLCExtensionsDialogProvider.h gui/macosx/VLCExtensionsDialogProvider.m \
	gui/macosx/VLCExtensionsManager.h gui/macosx/VLCExtensionsManager.m \
	gui/macosx/VLCHelpWindowController.h gui/macosx/VLCHelpWindowController.m \
	gui/macosx/VLCMain+OldPrefs.h gui/macosx/VLCMain+OldPrefs.m \
	gui/macosx/VLCMain.h gui/macosx/VLCMain.m \
	gui/macosx/VLCApplication.h gui/macosx/VLCApplication.m \
	gui/macosx/iTunes.h \
	gui/macosx/VLCKeyboardBacklightControl.h gui/macosx/VLCKeyboardBacklightControl.m \
	gui/macosx/macosx.m \
	gui/macosx/VLCMainMenu.h gui/macosx/VLCMainMenu.m \
	gui/macosx/VLCMainWindowTitleView.h gui/macosx/VLCMainWindowTitleView.m \
	gui/macosx/misc.h gui/macosx/misc.m \
	gui/macosx/NSGradient+VLCAdditions.h gui/macosx/NSGradient+VLCAdditions.m \
	gui/macosx/NSSound+VLCAdditions.h gui/macosx/NSSound+VLCAdditions.m \
	gui/macosx/NSScreen+VLCAdditions.h gui/macosx/NSScreen+VLCAdditions.m \
	gui/macosx/VLCOpenWindowController.h gui/macosx/VLCOpenWindowController.m \
	gui/macosx/VLCOutput.h gui/macosx/VLCOutput.m \
	gui/macosx/VLCPlaylistView.h gui/macosx/VLCPlaylistView.m \
	gui/macosx/VLCPlaylist.h gui/macosx/VLCPlaylist.m \
	gui/macosx/VLCPlaylistInfo.h gui/macosx/VLCPlaylistInfo.m \
	gui/macosx/VLCPLItem.h gui/macosx/VLCPLItem.m \
	gui/macosx/VLCPLModel.h gui/macosx/VLCPLModel.m \
	gui/macosx/prefs.h gui/macosx/prefs.m \
	gui/macosx/prefs_widgets.h gui/macosx/prefs_widgets.m \
	gui/macosx/VLCPopupPanelController.h gui/macosx/VLCPopupPanelController.m \
	gui/macosx/VLCTextfieldPanelController.h gui/macosx/VLCTextfieldPanelController.m \
	gui/macosx/VLCSimplePrefsController.h gui/macosx/VLCSimplePrefsController.m \
	gui/macosx/VLCSimplePrefsWindow.h gui/macosx/VLCSimplePrefsWindow.m \
	gui/macosx/VLCHotkeyChangeWindow.h gui/macosx/VLCHotkeyChangeWindow.m \
	gui/macosx/SPMediaKeyTap.h gui/macosx/SPMediaKeyTap.m \
	gui/macosx/Spotify.h \
	gui/macosx/VLCStringUtility.h gui/macosx/VLCStringUtility.m \
	gui/macosx/VLCVoutView.h gui/macosx/VLCVoutView.m \
	gui/macosx/VLCTimeSelectionPanelController.h gui/macosx/VLCTimeSelectionPanelController.m \
	gui/macosx/VLCUIWidgets.h gui/macosx/VLCUIWidgets.m \
	gui/macosx/VLCScrollingClipView.h gui/macosx/VLCScrollingClipView.m \
	gui/macosx/VLCStatusBarIcon.h gui/macosx/VLCStatusBarIcon.m \
	gui/macosx/VLCVoutWindowController.h gui/macosx/VLCVoutWindowController.m \
	gui/macosx/Windows.h gui/macosx/Windows.m \
	gui/macosx/VLCAudioEffectsWindowController.h gui/macosx/VLCAudioEffectsWindowController.m \
	gui/macosx/VLCBookmarksWindowController.h gui/macosx/VLCBookmarksWindowController.m \
	gui/macosx/VLCBottomBarView.h gui/macosx/VLCBottomBarView.m \
	gui/macosx/VLCCoreDialogProvider.h gui/macosx/VLCCoreDialogProvider.m \
	gui/macosx/VLCLogMessage.h gui/macosx/VLCLogMessage.m \
	gui/macosx/VLCLogWindowController.h gui/macosx/VLCLogWindowController.m \
	gui/macosx/VLCHUDSliderCell.h gui/macosx/VLCHUDSliderCell.m \
	gui/macosx/VLCHUDButtonCell.h gui/macosx/VLCHUDButtonCell.m \
	gui/macosx/VLCHUDCheckboxCell.h gui/macosx/VLCHUDCheckboxCell.m \
	gui/macosx/VLCHUDTextFieldCell.h gui/macosx/VLCHUDTextFieldCell.m \
	gui/macosx/VLCHUDScroller.h gui/macosx/VLCHUDScroller.m \
	gui/macosx/VLCHUDOutlineView.h gui/macosx/VLCHUDOutlineView.m \
	gui/macosx/VLCHUDTableView.h gui/macosx/VLCHUDTableView.m \
	gui/macosx/VLCHUDTableCornerView.h gui/macosx/VLCHUDTableCornerView.m \
	gui/macosx/VLCHUDSegmentedCell.h gui/macosx/VLCHUDSegmentedCell.m \
	gui/macosx/VLCHUDStepperCell.h gui/macosx/VLCHUDStepperCell.m \
	gui/macosx/VLCHUDPopUpButtonCell.h gui/macosx/VLCHUDPopUpButtonCell.m \
	gui/macosx/VLCInputManager.h gui/macosx/VLCInputManager.m \
	gui/macosx/VLCMainWindow.h gui/macosx/VLCMainWindow.m \
	gui/macosx/VLCRendererDiscovery.h gui/macosx/VLCRendererDiscovery.m \
	gui/macosx/VLCRendererItem.h gui/macosx/VLCRendererItem.m \
	gui/macosx/VLCRendererMenuController.h gui/macosx/VLCRendererMenuController.m \
	gui/macosx/VLCResumeDialogController.h gui/macosx/VLCResumeDialogController.m \
	gui/macosx/VLCSidebarDataSource.h gui/macosx/VLCSidebarDataSource.m \
	gui/macosx/VLCSourceListItem.h gui/macosx/VLCSourceListItem.m \
	gui/macosx/VLCSourceListTableCellView.h gui/macosx/VLCSourceListTableCellView.m \
	gui/macosx/VLCSourceListBadgeButton.h gui/macosx/VLCSourceListBadgeButton.m \
	gui/macosx/VLCTrackSynchronizationWindowController.h gui/macosx/VLCTrackSynchronizationWindowController.m \
	gui/macosx/VLCVideoEffectsWindowController.h gui/macosx/VLCVideoEffectsWindowController.m \
	gui/macosx/VLCFSPanelController.h gui/macosx/VLCFSPanelController.m \
	gui/macosx/VLCFSPanelDraggableView.h gui/macosx/VLCFSPanelDraggableView.m \
	gui/macosx/VLCDefaultValueSlider.h gui/macosx/VLCDefaultValueSlider.m \
	gui/macosx/VLCDefaultValueSliderCell.h gui/macosx/VLCDefaultValueSliderCell.m \
	gui/macosx/VLCImageButton.h gui/macosx/VLCImageButton.m \
	gui/macosx/VLCTintedImageButtonCell.h gui/macosx/VLCTintedImageButtonCell.m \
	gui/macosx/VLCTimeField.h gui/macosx/VLCTimeField.m \
	gui/macosx/VLCHexNumberFormatter.h gui/macosx/VLCHexNumberFormatter.m \
	gui/macosx/VLCSlider.h gui/macosx/VLCSlider.m \
	gui/macosx/VLCSliderCell.h gui/macosx/VLCSliderCell.m \
	gui/macosx/VLCVolumeSlider.h gui/macosx/VLCVolumeSlider.m \
	gui/macosx/VLCVolumeSliderCell.h gui/macosx/VLCVolumeSliderCell.m \
	gui/macosx/VLCWrappableTextField.h gui/macosx/VLCWrappableTextField.m \
	gui/macosx/VLCRemoteControlService.h gui/macosx/VLCRemoteControlService.m
>>>>>>> origin/3.0.x

# PXSourceList sources
libmacosx_plugin_la_SOURCES += \
	gui/macosx/PXSourceList/PXSourceList.h \
	gui/macosx/PXSourceList/PXSourceList.m \
	gui/macosx/PXSourceList/PXSourceListBadgeCell.h \
	gui/macosx/PXSourceList/PXSourceListBadgeCell.m \
	gui/macosx/PXSourceList/PXSourceListBadgeView.h \
	gui/macosx/PXSourceList/PXSourceListBadgeView.m \
	gui/macosx/PXSourceList/PXSourceListItem.h \
	gui/macosx/PXSourceList/PXSourceListItem.m \
	gui/macosx/PXSourceList/PXSourceListTableCellView.h \
	gui/macosx/PXSourceList/PXSourceListTableCellView.m \
	gui/macosx/PXSourceList/Internal/PXSourceListDelegateDataSourceProxy.h \
	gui/macosx/PXSourceList/Internal/PXSourceListDelegateDataSourceProxy.m \
	gui/macosx/PXSourceList/Internal/PXSourceListRuntimeAdditions.h \
	gui/macosx/PXSourceList/Internal/PXSourceListRuntimeAdditions.m \
	gui/macosx/PXSourceList/Internal/PXSourceListPrivateConstants.h \
	gui/macosx/PXSourceList/PXSourceListDataSource.h \
	gui/macosx/PXSourceList/PXSourceListDelegate.h

# User interface compilation

libmacosx_plugin_la_XIB_SOURCES = \
	gui/macosx/UI/About.xib \
	gui/macosx/UI/AddonManager.xib \
	gui/macosx/UI/AudioEffects.xib \
	gui/macosx/UI/Bookmarks.xib \
	gui/macosx/UI/ConvertAndSave.xib \
	gui/macosx/UI/CoreDialogs.xib \
	gui/macosx/UI/ErrorPanel.xib \
	gui/macosx/UI/Help.xib \
	gui/macosx/UI/LogMessageWindow.xib \
	gui/macosx/UI/MainMenu.xib \
	gui/macosx/UI/VLCCustomCropARPanel.xib \
	gui/macosx/UI/VLCDetachedAudioWindow.xib \
	gui/macosx/UI/VLCLibraryAlbumTableCellView.xib \
	gui/macosx/UI/VLCLibraryInformationPanel.xib \
	gui/macosx/UI/VLCLibraryWindow.xib \
	gui/macosx/UI/VLCLibraryTableCellView.xib \
	gui/macosx/UI/VLCPlaylistTableCellView.xib \
	gui/macosx/UI/VLCLibraryCollectionViewItem.xib \
	gui/macosx/UI/VLCLibraryCollectionViewAlbumSupplementaryDetailView.xib \
	gui/macosx/UI/VLCLibraryCollectionViewAudioGroupSupplementaryDetailView.xib \
	gui/macosx/UI/VLCLibraryCollectionViewMediaItemSupplementaryDetailView.xib \
	gui/macosx/UI/VLCLibrarySongTableCellView.xib \
	gui/macosx/UI/VLCMainVideoView.xib \
	gui/macosx/UI/VLCMediaSourceCollectionViewItem.xib \
	gui/macosx/UI/VLCMediaSourceDeviceCollectionViewItem.xib \
	gui/macosx/UI/VLCInformationWindow.xib \
	gui/macosx/UI/Open.xib \
	gui/macosx/UI/PlaylistAccessoryView.xib \
	gui/macosx/UI/PopupPanel.xib \
	gui/macosx/UI/Preferences.xib \
	gui/macosx/UI/ResumeDialog.xib \
	gui/macosx/UI/SimplePreferences.xib \
	gui/macosx/UI/StreamOutput.xib \
	gui/macosx/UI/SyncTracks.xib \
	gui/macosx/UI/TextfieldPanel.xib \
	gui/macosx/UI/TimeSelectionPanel.xib \
	gui/macosx/UI/VideoEffects.xib \
	gui/macosx/UI/VLCFullScreenPanel.xib \
	gui/macosx/UI/VLCStatusBarIconMainMenu.xib

libmacosx_plugin_la_SOURCES += $(libmacosx_plugin_la_XIB_SOURCES)

if ENABLE_MACOSX_UI
gui_LTLIBRARIES += libmacosx_plugin.la
BUILT_SOURCES += $(libmacosx_plugin_la_XIB_SOURCES:.xib=.nib)
endif


libmacosx_plugin_la_RES = \
	gui/macosx/Resources/App-Icons/VLC-Xmas.icns \
	gui/macosx/Resources/App-Icons/VLC.icns \
	gui/macosx/Resources/File-Icons/aiff.icns \
	gui/macosx/Resources/File-Icons/audio.icns \
	gui/macosx/Resources/File-Icons/avi.icns \
	gui/macosx/Resources/File-Icons/flv.icns \
	gui/macosx/Resources/File-Icons/generic.icns \
	gui/macosx/Resources/File-Icons/m4a.icns \
	gui/macosx/Resources/File-Icons/m4v.icns \
	gui/macosx/Resources/File-Icons/mkv.icns \
	gui/macosx/Resources/File-Icons/mov.icns \
	gui/macosx/Resources/File-Icons/movie.icns \
	gui/macosx/Resources/File-Icons/mp3.icns \
	gui/macosx/Resources/File-Icons/mpeg.icns \
	gui/macosx/Resources/File-Icons/ogg.icns \
	gui/macosx/Resources/File-Icons/playlist.icns \
	gui/macosx/Resources/File-Icons/rm.icns \
	gui/macosx/Resources/File-Icons/subtitle.icns \
	gui/macosx/Resources/File-Icons/vob.icns \
	gui/macosx/Resources/File-Icons/wav.icns \
	gui/macosx/Resources/File-Icons/wma.icns \
	gui/macosx/Resources/File-Icons/wmv.icns \
	gui/macosx/Resources/browsewindow/bw-Music.png \
	gui/macosx/Resources/browsewindow/bw-Music@2x.png \
	gui/macosx/Resources/browsewindow/bw-Music@3x.png \
	gui/macosx/Resources/browsewindow/bw-Podcast.png \
	gui/macosx/Resources/browsewindow/bw-Podcast@1,5x.svg \
	gui/macosx/Resources/browsewindow/bw-Podcast@2x.png \
	gui/macosx/Resources/browsewindow/bw-Podcast@3x.png \
	gui/macosx/Resources/browsewindow/bw-Server1.png \
	gui/macosx/Resources/browsewindow/bw-Server1@2x.png \
	gui/macosx/Resources/browsewindow/bw-Server1@3x.png \
	gui/macosx/Resources/browsewindow/bw-blu-ray.png \
	gui/macosx/Resources/browsewindow/bw-blu-ray@2x.png \
	gui/macosx/Resources/browsewindow/bw-blu-ray@3x.png \
	gui/macosx/Resources/browsewindow/bw-home.png \
	gui/macosx/Resources/browsewindow/bw-home@2x.png \
	gui/macosx/Resources/browsewindow/bw-home@3x.png \
	gui/macosx/Resources/browsewindow/bw-phone.png \
	gui/macosx/Resources/browsewindow/bw-phone@2x.png \
	gui/macosx/Resources/browsewindow/bw-phone@3x.png \
	gui/macosx/Resources/browsewindow/bw-server2.png \
	gui/macosx/Resources/browsewindow/bw-server2@2x.png \
	gui/macosx/Resources/browsewindow/bw-server2@3x.png \
	gui/macosx/Resources/browsewindow/bw-usb1.png \
	gui/macosx/Resources/browsewindow/bw-usb1@2x.png \
	gui/macosx/Resources/browsewindow/bw-usb1@3x.png \
	gui/macosx/Resources/browsewindow/bw-usb2.png \
	gui/macosx/Resources/browsewindow/bw-usb2@2x.png \
	gui/macosx/Resources/browsewindow/bw-usb2@3x.png \
	gui/macosx/Resources/browsewindow/bw-video.png \
	gui/macosx/Resources/browsewindow/bw-video@2x.png \
	gui/macosx/Resources/browsewindow/bw-video@3x.png \
	gui/macosx/Resources/librarywindow/ellipsis.png \
	gui/macosx/Resources/librarywindow/ellipsis@2x.png \
	gui/macosx/Resources/librarywindow/note.png \
	gui/macosx/Resources/librarywindow/note@2x.png \
	gui/macosx/Resources/librarywindow/libraryPlay.png \
	gui/macosx/Resources/librarywindow/libraryPlay@2x.png \
	gui/macosx/Resources/librarywindow/repeatAll.png \
	gui/macosx/Resources/librarywindow/repeatAll@2x.png \
	gui/macosx/Resources/librarywindow/repeatOff.png \
	gui/macosx/Resources/librarywindow/repeatOff@2x.png \
	gui/macosx/Resources/librarywindow/repeatOne.png \
	gui/macosx/Resources/librarywindow/repeatOne@2x.png \
	gui/macosx/Resources/librarywindow/shuffleOff.png \
	gui/macosx/Resources/librarywindow/shuffleOff@2x.png \
	gui/macosx/Resources/librarywindow/shuffleOn.png \
	gui/macosx/Resources/librarywindow/shuffleOn@2x.png \
	gui/macosx/Resources/mainwindow/album.png \
	gui/macosx/Resources/mainwindow/album@2x.png \
	gui/macosx/Resources/mainwindow/artist.png \
	gui/macosx/Resources/mainwindow/artist@2x.png \
	gui/macosx/Resources/mainwindow/backward-3btns-pressed.png \
	gui/macosx/Resources/mainwindow/backward-3btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow/backward-3btns.png \
	gui/macosx/Resources/mainwindow/backward-3btns@2x.png \
	gui/macosx/Resources/mainwindow/backward-6btns-pressed.png \
	gui/macosx/Resources/mainwindow/backward-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow/backward-6btns.png \
	gui/macosx/Resources/mainwindow/backward-6btns@2x.png \
	gui/macosx/Resources/mainwindow/dropzone-background.png \
	gui/macosx/Resources/mainwindow/dropzone.png \
	gui/macosx/Resources/mainwindow/dropzone@2x.png \
	gui/macosx/Resources/mainwindow/effects-double-buttons-pressed.png \
	gui/macosx/Resources/mainwindow/effects-double-buttons-pressed@2x.png \
	gui/macosx/Resources/mainwindow/effects-double-buttons.png \
	gui/macosx/Resources/mainwindow/effects-double-buttons@2x.png \
	gui/macosx/Resources/mainwindow/effects-one-button-pressed.png \
	gui/macosx/Resources/mainwindow/effects-one-button-pressed@2x.png \
	gui/macosx/Resources/mainwindow/effects-one-button.png \
	gui/macosx/Resources/mainwindow/effects-one-button@2x.png \
	gui/macosx/Resources/mainwindow/forward-3btns-pressed.png \
	gui/macosx/Resources/mainwindow/forward-3btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow/forward-3btns.png \
	gui/macosx/Resources/mainwindow/forward-3btns@2x.png \
	gui/macosx/Resources/mainwindow/forward-6btns-pressed.png \
	gui/macosx/Resources/mainwindow/forward-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow/forward-6btns.png \
	gui/macosx/Resources/mainwindow/forward-6btns@2x.png \
	gui/macosx/Resources/mainwindow/fullscreen-double-buttons-pressed.png \
	gui/macosx/Resources/mainwindow/fullscreen-double-buttons-pressed@2x.png \
	gui/macosx/Resources/mainwindow/fullscreen-double-buttons.png \
	gui/macosx/Resources/mainwindow/fullscreen-double-buttons@2x.png \
	gui/macosx/Resources/mainwindow/fullscreen-one-button-pressed.png \
	gui/macosx/Resources/mainwindow/fullscreen-one-button-pressed@2x.png \
	gui/macosx/Resources/mainwindow/fullscreen-one-button.png \
	gui/macosx/Resources/mainwindow/fullscreen-one-button@2x.png \
	gui/macosx/Resources/mainwindow/next-6btns-pressed.png \
	gui/macosx/Resources/mainwindow/next-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow/next-6btns.png \
	gui/macosx/Resources/mainwindow/next-6btns@2x.png \
	gui/macosx/Resources/mainwindow/pause-pressed.png \
	gui/macosx/Resources/mainwindow/pause-pressed@2x.png \
	gui/macosx/Resources/mainwindow/pause.png \
	gui/macosx/Resources/mainwindow/pause@2x.png \
	gui/macosx/Resources/mainwindow/placeholder-group2.pdf \
	gui/macosx/Resources/mainwindow/placeholder-group2.png \
	gui/macosx/Resources/mainwindow/placeholder-group2.svg \
	gui/macosx/Resources/mainwindow/placeholder-group2@2x.png \
	gui/macosx/Resources/mainwindow/placeholder-music.pdf \
	gui/macosx/Resources/mainwindow/placeholder-music.png \
	gui/macosx/Resources/mainwindow/placeholder-music.svg \
	gui/macosx/Resources/mainwindow/placeholder-music@2x.png \
	gui/macosx/Resources/mainwindow/placeholder-video.pdf \
	gui/macosx/Resources/mainwindow/placeholder-video.png \
	gui/macosx/Resources/mainwindow/placeholder-video.svg \
	gui/macosx/Resources/mainwindow/placeholder-video@2x.png \
	gui/macosx/Resources/mainwindow/play-pressed.png \
	gui/macosx/Resources/mainwindow/play-pressed@2x.png \
	gui/macosx/Resources/mainwindow/play.png \
	gui/macosx/Resources/mainwindow/play@2x.png \
	gui/macosx/Resources/mainwindow/playlist-1btn-pressed.png \
	gui/macosx/Resources/mainwindow/playlist-1btn-pressed@2x.png \
	gui/macosx/Resources/mainwindow/playlist-1btn.png \
	gui/macosx/Resources/mainwindow/playlist-1btn@2x.png \
	gui/macosx/Resources/mainwindow/playlist-btn-pressed.png \
	gui/macosx/Resources/mainwindow/playlist-btn-pressed@2x.png \
	gui/macosx/Resources/mainwindow/playlist-btn.png \
	gui/macosx/Resources/mainwindow/playlist-btn@2x.png \
	gui/macosx/Resources/mainwindow/previous-6btns-pressed.png \
	gui/macosx/Resources/mainwindow/previous-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow/previous-6btns.png \
	gui/macosx/Resources/mainwindow/previous-6btns@2x.png \
	gui/macosx/Resources/mainwindow/repeat-all-pressed.png \
	gui/macosx/Resources/mainwindow/repeat-all-pressed@2x.png \
	gui/macosx/Resources/mainwindow/repeat-all.png \
	gui/macosx/Resources/mainwindow/repeat-all@2x.png \
	gui/macosx/Resources/mainwindow/repeat-one-pressed.png \
	gui/macosx/Resources/mainwindow/repeat-one-pressed@2x.png \
	gui/macosx/Resources/mainwindow/repeat-one.png \
	gui/macosx/Resources/mainwindow/repeat-one@2x.png \
	gui/macosx/Resources/mainwindow/repeat-pressed.png \
	gui/macosx/Resources/mainwindow/repeat-pressed@2x.png \
	gui/macosx/Resources/mainwindow/repeat.png \
	gui/macosx/Resources/mainwindow/repeat@2x.png \
	gui/macosx/Resources/mainwindow/shuffle-blue-pressed.png \
	gui/macosx/Resources/mainwindow/shuffle-blue-pressed@2x.png \
	gui/macosx/Resources/mainwindow/shuffle-blue.png \
	gui/macosx/Resources/mainwindow/shuffle-blue@2x.png \
	gui/macosx/Resources/mainwindow/shuffle-pressed.png \
	gui/macosx/Resources/mainwindow/shuffle-pressed@2x.png \
	gui/macosx/Resources/mainwindow/shuffle.png \
	gui/macosx/Resources/mainwindow/shuffle@2x.png \
	gui/macosx/Resources/mainwindow/stop-pressed.png \
	gui/macosx/Resources/mainwindow/stop-pressed@2x.png \
	gui/macosx/Resources/mainwindow/stop.png \
	gui/macosx/Resources/mainwindow/stop@2x.png \
	gui/macosx/Resources/mainwindow/topbar_background.png \
	gui/macosx/Resources/mainwindow/video.png \
	gui/macosx/Resources/mainwindow/video@2x.png \
	gui/macosx/Resources/mainwindow/volume-high.png \
	gui/macosx/Resources/mainwindow/volume-high@2x.png \
	gui/macosx/Resources/mainwindow/volume-low.png \
	gui/macosx/Resources/mainwindow/volume-low@2x.png \
<<<<<<< master
=======
	gui/macosx/Resources/mainwindow_dark/backward-3btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/backward-3btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/backward-3btns-dark.png \
	gui/macosx/Resources/mainwindow_dark/backward-3btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/backward-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/backward-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/backward-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark/backward-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/effects-double-buttons-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/effects-double-buttons-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/effects-double-buttons_dark.png \
	gui/macosx/Resources/mainwindow_dark/effects-double-buttons_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/effects-one-button-pressed-dark.png \
	gui/macosx/Resources/mainwindow_dark/effects-one-button-pressed-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/effects-one-button_dark.png \
	gui/macosx/Resources/mainwindow_dark/effects-one-button_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/forward-3btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/forward-3btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/forward-3btns-dark.png \
	gui/macosx/Resources/mainwindow_dark/forward-3btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/forward-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/forward-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/forward-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark/forward-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-double-buttons-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-double-buttons-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-double-buttons_dark.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-double-buttons_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-one-button-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-one-button-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-one-button_dark.png \
	gui/macosx/Resources/mainwindow_dark/fullscreen-one-button_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/next-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/next-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/next-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark/next-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/pause-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/pause-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/pause_dark.png \
	gui/macosx/Resources/mainwindow_dark/pause_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/play-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/play-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/play_dark.png \
	gui/macosx/Resources/mainwindow_dark/play_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/playlist-1btn-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/playlist-1btn-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/playlist-1btn-dark.png \
	gui/macosx/Resources/mainwindow_dark/playlist-1btn-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/playlist-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/playlist-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/playlist_dark.png \
	gui/macosx/Resources/mainwindow_dark/playlist_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/previous-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark/previous-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark/previous-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark/previous-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/repeat-all-blue-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/repeat-all-blue-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/repeat-all-blue_dark.png \
	gui/macosx/Resources/mainwindow_dark/repeat-all-blue_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/repeat-one-blue-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/repeat-one-blue-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/repeat-one-blue_dark.png \
	gui/macosx/Resources/mainwindow_dark/repeat-one-blue_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/repeat-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/repeat-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/repeat_dark.png \
	gui/macosx/Resources/mainwindow_dark/repeat_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/shuffle-blue-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/shuffle-blue-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/shuffle-blue_dark.png \
	gui/macosx/Resources/mainwindow_dark/shuffle-blue_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/shuffle-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/shuffle-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/shuffle_dark.png \
	gui/macosx/Resources/mainwindow_dark/shuffle_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/stop-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark/stop-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/stop_dark.png \
	gui/macosx/Resources/mainwindow_dark/stop_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-close@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-fullscreen-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-fullscreen-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-fullscreen-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-fullscreen-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-fullscreen.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-fullscreen@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-minimize@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/lion/lion-window-zoom@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-close@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-fullscreen@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-minimize@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-on-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-on-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-on.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-on@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-over-graphite.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-over-graphite@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-over.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom-over@2x.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom.png \
	gui/macosx/Resources/mainwindow_dark/titlebar/yosemite/yosemite-window-zoom@2x.png \
	gui/macosx/Resources/mainwindow_dark/topbar-dark-center-fill.png \
	gui/macosx/Resources/mainwindow_dark/topbar-dark-center-fill@2x.png \
	gui/macosx/Resources/mainwindow_dark/topbar-dark-left.png \
	gui/macosx/Resources/mainwindow_dark/topbar-dark-left@2x.png \
	gui/macosx/Resources/mainwindow_dark/topbar-dark-right.png \
	gui/macosx/Resources/mainwindow_dark/topbar-dark-right@2x.png \
	gui/macosx/Resources/mainwindow_dark/volume-high_dark.png \
	gui/macosx/Resources/mainwindow_dark/volume-high_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/volume-low_dark.png \
	gui/macosx/Resources/mainwindow_dark/volume-low_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark/window-resize.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-3btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-3btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-3btns-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-3btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-backward-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-double-buttons-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-double-buttons-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-double-buttons_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-double-buttons_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-one-button-pressed-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-one-button-pressed-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-one-button_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-effects-one-button_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-3btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-3btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-3btns-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-3btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-forward-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-double-buttons-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-double-buttons-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-double-buttons_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-double-buttons_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-one-button-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-one-button-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-one-button_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-fullscreen-one-button_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-next-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-next-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-next-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-next-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-pause-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-pause-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-pause_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-pause_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-play-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-play-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-play_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-play_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist-1btn-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist-1btn-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist-1btn-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist-1btn-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-playlist_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-previous-6btns-dark-pressed.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-previous-6btns-dark-pressed@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-previous-6btns-dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-previous-6btns-dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-all-blue-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-all-blue-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-all-blue_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-all-blue_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-one-blue-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-one-blue-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-one-blue_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-one-blue_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-repeat_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle-blue-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle-blue-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle-blue_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle-blue_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-shuffle_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-stop-pressed_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-stop-pressed_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-stop_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-stop_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-topbar-dark-center-fill.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-topbar-dark-center-fill@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-topbar-dark-left.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-topbar-dark-left@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-topbar-dark-right.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-topbar-dark-right@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-volume-high_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-volume-high_dark@2x.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-volume-low_dark.png \
	gui/macosx/Resources/mainwindow_dark_yosemite/ys-volume-low_dark@2x.png \
	gui/macosx/Resources/mainwindow_mojave_dark/mj-dropzone-dark.png \
	gui/macosx/Resources/mainwindow_mojave_dark/mj-dropzone-dark@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-3btns-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-3btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-3btns.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-3btns@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-6btns-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-6btns.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-backward-6btns@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-dropzone.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-dropzone@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-double-buttons-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-double-buttons-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-double-buttons.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-double-buttons@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-one-button-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-one-button-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-one-button.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-effects-one-button@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-3btns-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-3btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-3btns.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-3btns@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-6btns-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-6btns.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-forward-6btns@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-double-buttons-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-double-buttons-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-double-buttons.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-double-buttons@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-one-button-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-one-button-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-one-button.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-fullscreen-one-button@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-next-6btns-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-next-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-next-6btns.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-next-6btns@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-pause-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-pause-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-pause.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-pause@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-play-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-play-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-play.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-play@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-1btn-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-1btn-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-1btn.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-1btn@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-btn-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-btn-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-btn.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-playlist-btn@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-previous-6btns-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-previous-6btns-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-previous-6btns.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-previous-6btns@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-all-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-all-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-all.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-all@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-one-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-one-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-one.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-one@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-repeat@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle-blue-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle-blue-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle-blue.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle-blue@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-shuffle@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-stop-pressed.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-stop-pressed@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-stop.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-stop@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-volume-high.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-volume-high@2x.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-volume-low.png \
	gui/macosx/Resources/mainwindow_yosemite/ys-volume-low@2x.png \
>>>>>>> origin/3.0.x
	gui/macosx/Resources/noart.png \
	gui/macosx/Resources/Pref-Icons/VLCAudioCone.png \
	gui/macosx/Resources/Pref-Icons/VLCHotkeysCone.png \
	gui/macosx/Resources/Pref-Icons/VLCInputCone.png \
	gui/macosx/Resources/Pref-Icons/VLCInterfaceCone.png \
	gui/macosx/Resources/Pref-Icons/VLCSubtitleCone.png \
	gui/macosx/Resources/Pref-Icons/VLCVideoCone.png \
	gui/macosx/Resources/sidebar-icons/sidebar-movie.png \
	gui/macosx/Resources/sidebar-icons/sidebar-movie@2x.png \
	gui/macosx/Resources/sidebar-icons/sidebar-music.png \
	gui/macosx/Resources/sidebar-icons/sidebar-music@2x.png \
<<<<<<< master
=======
	gui/macosx/Resources/sidebar-icons/sidebar-pictures.png \
	gui/macosx/Resources/sidebar-icons/sidebar-pictures@2x.png \
	gui/macosx/Resources/sidebar-icons/sidebar-playlist.png \
	gui/macosx/Resources/sidebar-icons/sidebar-playlist@2x.png \
	gui/macosx/Resources/sidebar-icons/sidebar-podcast.png \
	gui/macosx/Resources/sidebar-icons/sidebar-podcast@2x.png \
	gui/macosx/Resources/sidebar-icons_mojave/dark/mv-dark-sidebar-local.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/dark/mv-dark-sidebar-movie.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/dark/mv-dark-sidebar-music.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/dark/mv-dark-sidebar-pictures.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/dark/mv-dark-sidebar-playlist.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/dark/mv-dark-sidebar-podcast.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/light/mv-sidebar-local.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/light/mv-sidebar-movie.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/light/mv-sidebar-music.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/light/mv-sidebar-pictures.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/light/mv-sidebar-playlist.pdf \
	gui/macosx/Resources/sidebar-icons_mojave/light/mv-sidebar-podcast.pdf \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-local.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-local@2x.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-movie.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-movie@2x.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-music.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-music@2x.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-pictures.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-pictures@2x.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-playlist.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-playlist@2x.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-podcast.png \
	gui/macosx/Resources/sidebar-icons_yosemite/ys-sidebar-podcast@2x.png \
>>>>>>> origin/3.0.x
	gui/macosx/Resources/Button-Icons/VLCNextTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCPauseTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCPlayTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCPreviousTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCShuffleTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCStatusBarIcon.pdf \
	gui/macosx/Resources/Button-Icons/VLCBackwardTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCForwardTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCFullscreenOnTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCFullscreenOffTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCVolumeOnTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCVolumeOffTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCClearLogTemplate.pdf \
	gui/macosx/Resources/Button-Icons/VLCSaveTemplate.pdf \
	gui/macosx/Resources/Button-Icons/window-close-graphite.png \
	gui/macosx/Resources/Button-Icons/window-close-graphite@2x.png \
	gui/macosx/Resources/Button-Icons/window-close-on-graphite.png \
	gui/macosx/Resources/Button-Icons/window-close-on-graphite@2x.png \
	gui/macosx/Resources/Button-Icons/window-close-on.png \
	gui/macosx/Resources/Button-Icons/window-close-on@2x.png \
	gui/macosx/Resources/Button-Icons/window-close-over-graphite.png \
	gui/macosx/Resources/Button-Icons/window-close-over-graphite@2x.png \
	gui/macosx/Resources/Button-Icons/window-close-over.png \
	gui/macosx/Resources/Button-Icons/window-close-over@2x.png \
	gui/macosx/Resources/Button-Icons/window-close.png \
	gui/macosx/Resources/Button-Icons/window-close@2x.png

libmacosx_plugin_la_RES += \
	gui/macosx/Resources/dsa_pub.pem \
	gui/macosx/Resources/README \
	gui/macosx/Resources/vlc.scriptSuite \
	gui/macosx/Resources/vlc.scriptTerminology

EXTRA_DIST += \
<<<<<<< master
	gui/macosx/Resources/Base.lproj/InfoPlist.strings \
	gui/macosx/Resources/ar.lproj/InfoPlist.strings \
	gui/macosx/Resources/bg.lproj/InfoPlist.strings \
	gui/macosx/Resources/ca.lproj/InfoPlist.strings \
	gui/macosx/Resources/cs.lproj/InfoPlist.strings \
	gui/macosx/Resources/de.lproj/InfoPlist.strings \
	gui/macosx/Resources/el.lproj/InfoPlist.strings \
	gui/macosx/Resources/es.lproj/InfoPlist.strings \
	gui/macosx/Resources/fr.lproj/InfoPlist.strings \
	gui/macosx/Resources/gl.lproj/InfoPlist.strings \
	gui/macosx/Resources/he.lproj/InfoPlist.strings \
	gui/macosx/Resources/hu.lproj/InfoPlist.strings \
	gui/macosx/Resources/it.lproj/InfoPlist.strings \
	gui/macosx/Resources/ja.lproj/InfoPlist.strings \
	gui/macosx/Resources/lv.lproj/InfoPlist.strings \
	gui/macosx/Resources/nl.lproj/InfoPlist.strings \
	gui/macosx/Resources/pl.lproj/InfoPlist.strings \
	gui/macosx/Resources/pt-BR.lproj/InfoPlist.strings \
	gui/macosx/Resources/pt-PT.lproj/InfoPlist.strings \
	gui/macosx/Resources/sk.lproj/InfoPlist.strings \
	gui/macosx/Resources/sl.lproj/InfoPlist.strings \
	gui/macosx/Resources/sv.lproj/InfoPlist.strings \
	gui/macosx/Resources/tr.lproj/InfoPlist.strings \
	gui/macosx/Resources/uk.lproj/InfoPlist.strings \
	gui/macosx/Resources/zh-Hans.lproj/InfoPlist.strings
=======
	gui/macosx/Resources/English.lproj/InfoPlist.strings \
	gui/macosx/Resources/an.lproj/InfoPlist.strings \
	gui/macosx/Resources/ar.lproj/InfoPlist.strings \
	gui/macosx/Resources/as-IN.lproj/InfoPlist.strings \
	gui/macosx/Resources/ast.lproj/InfoPlist.strings \
	gui/macosx/Resources/be.lproj/InfoPlist.strings \
	gui/macosx/Resources/bg.lproj/InfoPlist.strings \
	gui/macosx/Resources/bn-IN.lproj/InfoPlist.strings \
	gui/macosx/Resources/br.lproj/InfoPlist.strings \
	gui/macosx/Resources/brx.lproj/InfoPlist.strings \
	gui/macosx/Resources/ca.lproj/InfoPlist.strings \
	gui/macosx/Resources/co.lproj/InfoPlist.strings \
	gui/macosx/Resources/cs.lproj/InfoPlist.strings \
	gui/macosx/Resources/cy.lproj/InfoPlist.strings \
	gui/macosx/Resources/da.lproj/InfoPlist.strings \
	gui/macosx/Resources/de.lproj/InfoPlist.strings \
	gui/macosx/Resources/el.lproj/InfoPlist.strings \
	gui/macosx/Resources/en-GB.lproj/InfoPlist.strings \
	gui/macosx/Resources/es-MX.lproj/InfoPlist.strings \
	gui/macosx/Resources/es.lproj/InfoPlist.strings \
	gui/macosx/Resources/et.lproj/InfoPlist.strings \
	gui/macosx/Resources/eu.lproj/InfoPlist.strings \
	gui/macosx/Resources/fa.lproj/InfoPlist.strings \
	gui/macosx/Resources/fi.lproj/InfoPlist.strings \
	gui/macosx/Resources/fr.lproj/InfoPlist.strings \
	gui/macosx/Resources/ga.lproj/InfoPlist.strings \
	gui/macosx/Resources/gd.lproj/InfoPlist.strings \
	gui/macosx/Resources/gl.lproj/InfoPlist.strings \
	gui/macosx/Resources/gu-IN.lproj/InfoPlist.strings \
	gui/macosx/Resources/he.lproj/InfoPlist.strings \
	gui/macosx/Resources/hi.lproj/InfoPlist.strings \
	gui/macosx/Resources/hr.lproj/InfoPlist.strings \
	gui/macosx/Resources/hu.lproj/InfoPlist.strings \
	gui/macosx/Resources/id.lproj/InfoPlist.strings \
	gui/macosx/Resources/is.lproj/InfoPlist.strings \
	gui/macosx/Resources/it.lproj/InfoPlist.strings \
	gui/macosx/Resources/ja.lproj/InfoPlist.strings \
	gui/macosx/Resources/ka.lproj/InfoPlist.strings \
	gui/macosx/Resources/kab.lproj/InfoPlist.strings \
	gui/macosx/Resources/kk.lproj/InfoPlist.strings \
	gui/macosx/Resources/km.lproj/InfoPlist.strings \
	gui/macosx/Resources/kn.lproj/InfoPlist.strings \
	gui/macosx/Resources/ko.lproj/InfoPlist.strings \
	gui/macosx/Resources/ku.lproj/InfoPlist.strings \
	gui/macosx/Resources/lt.lproj/InfoPlist.strings \
	gui/macosx/Resources/lv.lproj/InfoPlist.strings \
	gui/macosx/Resources/ml.lproj/InfoPlist.strings \
	gui/macosx/Resources/mr.lproj/InfoPlist.strings \
	gui/macosx/Resources/ms.lproj/InfoPlist.strings \
	gui/macosx/Resources/my.lproj/InfoPlist.strings \
	gui/macosx/Resources/nb.lproj/InfoPlist.strings \
	gui/macosx/Resources/ne.lproj/InfoPlist.strings \
	gui/macosx/Resources/nl.lproj/InfoPlist.strings \
	gui/macosx/Resources/nn.lproj/InfoPlist.strings \
	gui/macosx/Resources/oc.lproj/InfoPlist.strings \
	gui/macosx/Resources/pa.lproj/InfoPlist.strings \
	gui/macosx/Resources/pl.lproj/InfoPlist.strings \
	gui/macosx/Resources/pt-BR.lproj/InfoPlist.strings \
	gui/macosx/Resources/pt-PT.lproj/InfoPlist.strings \
	gui/macosx/Resources/ro.lproj/InfoPlist.strings \
	gui/macosx/Resources/ru.lproj/InfoPlist.strings \
	gui/macosx/Resources/sat.lproj/InfoPlist.strings \
	gui/macosx/Resources/sc.lproj/InfoPlist.strings \
	gui/macosx/Resources/si.lproj/InfoPlist.strings \
	gui/macosx/Resources/sk.lproj/InfoPlist.strings \
	gui/macosx/Resources/sl.lproj/InfoPlist.strings \
	gui/macosx/Resources/sq.lproj/InfoPlist.strings \
	gui/macosx/Resources/sr.lproj/InfoPlist.strings \
	gui/macosx/Resources/sv.lproj/InfoPlist.strings \
	gui/macosx/Resources/th.lproj/InfoPlist.strings \
	gui/macosx/Resources/tr.lproj/InfoPlist.strings \
	gui/macosx/Resources/uk.lproj/InfoPlist.strings \
	gui/macosx/Resources/vi.lproj/InfoPlist.strings \
	gui/macosx/Resources/wa.lproj/InfoPlist.strings \
	gui/macosx/Resources/zh-Hans.lproj/InfoPlist.strings \
	gui/macosx/Resources/zh-Hant.lproj/InfoPlist.strings
>>>>>>> origin/3.0.x

if ENABLE_MACOSX_UI
dist_libmacosx_plugin_la_DATA = $(libmacosx_plugin_la_RES)
endif
libmacosx_plugin_ladir = $(prefix)/share/macosx/Contents/Resources
